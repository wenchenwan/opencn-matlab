function ctx = compressCurvStructs(ctx)
% CompressCurvStructs : 
% - Is feeded by the queue : q_gcode
% - Check if a compression is possible based on the individual curves 
% length, the cummulative length and the collinearity of two consecutive 
% segment. 
% - Check speed boundaries conditions (ZZ,ZN,NZ,NN) and split the curves
% accordingly.
% - Create a Bspline based on Lee89.
% - Fill the queue : q_compress
%
% Note : If compression is not required call ExpandZeroStructs

if ctx.q_gcode.isempty()
    return;
end

spline_index = ctx.q_spline.size() + 1;    % New index in q_spline
Ncrv = ctx.q_gcode.size;                    % Number of curve in g-code queue
Length_Threshold = ctx.cfg.LThreshold;      % in [mm]
NAxis = ctx.cfg.NumberAxis;

CumulatedLength = 0;                        % Accumulator for the length
spindle_speed = 75000;                      % in [rpm]

DebugLog(DebugCfg.Validate, 'Compressing...\n');

% Satisfy coder
if coder.target('rtw') || coder.target('mex')
    pvec = zeros(NAxis, 0);
    coder.varsize('pvec', [NAxis, Inf], [1, 1]);
    CurvStruct1 = ctx.q_gcode.get(1);
end

k = 1; % index for the Gcode queue

while k <= Ncrv
    Curv = ctx.q_gcode.get(k);          % Get next Curv in the queue
    % If the next curve segment is too long for compressing or it is not an NN,
    % we need to stop growing the compressing list and create the spline
    Collinear = false;                  % Set down collinear flag
    if k > 1      % Check colinearity with previous segment
        prevCurv = ctx.q_gcode.get(k-1);
        Collinear = curvCollinear(ctx, prevCurv, Curv, ...
                                  ctx.cfg.Compressing.ColTolCos);
    end
    
    % A new spline is created if one of the following conditions is met :
    %  - The length of the current curve is too long for the compressing
    %  - One of the boundaries speed is zero
    % No more segment is added to the list of compressing curves
    if ( Curv.Info.Type ~= CurveType.Line ) || ...                  % Not a Line
       ( LengthCurv(ctx, Curv, 0, 1) >= Length_Threshold ) || ...   % Too long segment
       ( Curv.Info.zspdmode == ZSpdMode.NZ ) || ...                 % Zero stop
       ( (k == Ncrv) && (CumulatedLength ~= 0) ) || ...             % Last segment and on-going compression
       ( ~Collinear && (k ~= 1) )                                   % Not collinear and not 1rst segment

        % In this case add the last segment
        if ( Curv.Info.zspdmode == ZSpdMode.NZ ) || ...             % Zero stop
           ( (k==Ncrv) && (CumulatedLength ~= 0) ) && ...           % Last segment and on-going compression
           ( CumulatedLength ~= 0 )
            P1 = EvalCurvStruct(ctx, Curv, 1);
            pvec = [pvec P1];
            zspdmodevec = [zspdmodevec Curv.Info.zspdmode];
            spindle_speed = min(spindle_speed, Curv.Info.SpindleSpeed);
        end

        % If the cumulated length is zero, no compressing is on-going.
        % The segment is treated individually 
        if CumulatedLength == 0
                ctx.q_compress.push(Curv);

        % If there was an on-going compression
        else           
            % We have more than 2 points, thus constructing a spline 
            % is warranted     
            if size(pvec, 2) > 2
                SplineCurve          = constrCurvStructType;
                SplineCurve.sp_index = spline_index;
                SplineCurve.sp       = CalcBspline_Lee(ctx.cfg, pvec);
                [Ltot, Lk]           = SplineLengthApproxGL_tot(ctx, SplineCurve);
                SplineCurve.sp.Ltot  = Ltot;
                SplineCurve.sp.Lk    = Lk;
                
                spline = constrSplineStruct( Curv.Info, pvec(:,1), ...
                                             pvec(:,end), int32(spline_index) );

                % Calculate the ZSpdMode for the spline
                if zspdmodevec(1) == ZSpdMode.NN && zspdmodevec(end) == ZSpdMode.NN
                    spline.Info.zspdmode = ZSpdMode.NN;
                    SplineCurve.Info.zspdmode = ZSpdMode.NN;
                elseif zspdmodevec(1) == ZSpdMode.NN && zspdmodevec(end) == ZSpdMode.NZ
                    spline.Info.zspdmode = ZSpdMode.NZ;
                    SplineCurve.Info.zspdmode = ZSpdMode.NZ;
                elseif zspdmodevec(1) == ZSpdMode.ZN && zspdmodevec(end) == ZSpdMode.NN
                    spline.Info.zspdmode = ZSpdMode.ZN;
                    SplineCurve.Info.zspdmode = ZSpdMode.ZN;
                elseif zspdmodevec(1) == ZSpdMode.ZN && zspdmodevec(end) == ZSpdMode.NZ
                    spline.Info.zspdmode = ZSpdMode.ZZ;
                    SplineCurve.Info.zspdmode = ZSpdMode.ZZ;
                else
                    fprintf('ERROR IN ZSPDMODE');
                end
                
                ctx.q_spline.push( SplineCurve );
                ctx.q_compress.push( spline );

                spline_index = spline_index + 1;

            % With only two points, construct a line
            else
                prevCurv.Info.gcode_source_line = Curv.Info.gcode_source_line;
                ctx.q_compress.push(prevCurv); % push segment to q_compress
                ctx.q_compress.push(Curv);     % push segment to q_compress
            end
            CumulatedLength = 0;
        end
    % In the general case with an elligible segment, add it to the
    % compression list
    else
        if CumulatedLength == 0
            P0 = EvalCurvStruct(ctx, Curv, 0);
            pvec = P0;
            spindle_speed = Curv.Info.SpindleSpeed;
            zspdmodevec = Curv.Info.zspdmode;
        end

        CumulatedLength = CumulatedLength + LengthCurv(ctx, Curv, 0, 1);
        P1 = EvalCurvStruct(ctx, Curv, 1);
        pvec = [pvec P1];
        zspdmodevec = [zspdmodevec Curv.Info.zspdmode];
        spindle_speed = min(spindle_speed, Curv.Info.SpindleSpeed);
    end
    k = k + 1;
end

end

