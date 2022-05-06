function ctx = CompressCurvStructs(ctx)
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

CumulatedLength = 0;                        % Accumulator for the length
spindle_speed = 75000;                      % in [rpm]

DebugLog(DebugCfg.Validate, 'Compressing...\n');

% Satisfy coder
if coder.target('rtw') || coder.target('mex')
    pvec = zeros(3, 0);
    coder.varsize('pvec', [3, Inf], [1, 1]);
    CurvStruct1 = ctx.q_gcode.get(1);
end

k = 1; % index for the Gcode queue

while k <= Ncrv
    Curv = ctx.q_gcode.get(k);          % Get next Curv in the queue
    % If the next curve segment is too long for compressing or it is not an NN,
    % we need to stop growing the compressing list and create the spline
    Collinear = false;                  % Set down collinear flag
    if k > 1      % Check colinearity with previous segment
        Collinear = curvCollinear(ctx, ctx.q_gcode.get(k-1), Curv, ...
                                  ctx.cfg.Compressing.ColTolCos);
    end
    
    % A new spline is created if one of the following conditions is met :
    %  - The length of the current curve is too long for the compressing
    %  - One of the boundaries speed is zero
    % No more segment is added to the list of compressing curves
    if ( LengthCurv(ctx, Curv, 0, 1) >= Length_Threshold ) || ...
       ( Curv.Info.zspdmode ~= ZSpdMode.NN ) ||...
       ( CumulatedLength == 0 && ~Collinear )

        % If the cumulated length is zero, no compressing is on-going.
        % The segment is treated individually 
        if CumulatedLength == 0
            % Depending of the speed at the boundary, the segment is split
            % and then send to q_compress.
            if Curv.Info.zspdmode == ZSpdMode.ZN
                [CurvStruct1_C, CurvStruct2_C] = cutZeroStart(ctx, Curv);
                ctx.q_compress.push(CurvStruct1_C);
                ctx.q_compress.push(CurvStruct2_C);
            elseif Curv.Info.zspdmode == ZSpdMode.NZ
                [CurvStruct1_C, CurvStruct2_C] = cutZeroEnd(ctx, Curv);
                ctx.q_compress.push(CurvStruct1_C);
                ctx.q_compress.push(CurvStruct2_C);
            elseif Curv.Info.zspdmode == ZSpdMode.ZZ
                [CurvStruct1_C, CurvStruct2_C] = cutZeroStart(ctx, Curv);
                [CurvStruct2_C, CurvStruct3_C] = cutZeroEnd(ctx, CurvStruct2_C);
                ctx.q_compress.push(CurvStruct1_C);
                ctx.q_compress.push(CurvStruct2_C);
                ctx.q_compress.push(CurvStruct3_C);
            else
                ctx.q_compress.push(Curv);
            end

        % If there was an on-going compression
        else           
            % We have more than 2 points, thus constructing a spline 
            % is warranted     
            if size(pvec, 2) > 2
                SplineCurve     = constrCurvStructType;
                SplineCurve.sp_index = spline_index;
                SplineCurve.sp  = CalcBspline_Lee(ctx.cfg, pvec);
                [Ltot, Lk]      = SplineLengthApproxGL_tot(ctx, SplineCurve);
                SplineCurve.sp.Ltot = Ltot;
                SplineCurve.sp.Lk   = Lk;
                ctx.q_spline.push( SplineCurve );
                spline = constrSplineStruct( Curv.Info, pvec(:,1), ...
                    pvec(:,end), int32(spline_index) );
                spline_index = spline_index + 1;
                ctx.q_compress.push(spline);

                if Curv.Info.zspdmode == ZSpdMode.NZ
                    [CurvStruct1_C, CurvStruct2_C] = cutZeroEnd(ctx, Curv);
                    ctx.q_compress.push(CurvStruct1_C);
                    ctx.q_compress.push(CurvStruct2_C);
                else
                    ctx.q_compress.push(Curv);
                end
            % With only two points, construct a line
            else
                C = ctx.q_gcode.get(k-1);   % get the previous segment
                C.gcode_source_line=Curv.gcode_source_line;
                ctx.q_compress.push(C);     % push segment to q_compress

                if Curv.Info.zspdmode == ZSpdMode.NZ % split if zero end
                    [CurvStruct1_C, CurvStruct2_C] = cutZeroEnd(ctx, Curv);
                    ctx.q_compress.push(CurvStruct1_C);
                    ctx.q_compress.push(CurvStruct2_C);
                else
                    ctx.q_compress.push(Curv); % push segment to q_compress
                end
            end
            CumulatedLength = 0;
        end
    % If this is the last segment and we have something in the
    % compression list, construct the spline
    elseif (k==Ncrv) && (CumulatedLength ~= 0)
        SplineCurve = constrCurvStructType;
        SplineCurve.sp=CalcBspline_Lee(ctx.cfg, pvec);
        [Ltot, Lk]     = SplineLengthApproxGL_tot(ctx, SplineCurve);
        SplineCurve.sp.Ltot = Ltot;                                 
        SplineCurve.sp.Lk   = Lk;                                    
        ctx.q_spline.push(SplineCurve);
        spline = constrSplineStruct( Curv.Info, pvec(:,1), ...
            pvec(:,end), int32(spline_index) );
        spline_index = spline_index + 1;
        ctx.q_compress.push(spline);

    % If this is the first (and elligible) WHAT
    elseif k==1
        ctx.q_compress.push(Curv);
    
    % In the general case with an elligible segment, add it to the
    % compression list
    else
        if CumulatedLength == 0
            P0 = EvalCurvStruct(ctx, Curv, 0);
            pvec = P0;
            spindle_speed = Curv.Info.SpindleSpeed;
        end

        CumulatedLength = CumulatedLength + LengthCurv(ctx, Curv, 0, 1);
        P1 = EvalCurvStruct(ctx, Curv, 1);
        pvec = [pvec P1];
        spindle_speed = min(spindle_speed, Curv.Info.SpindleSpeed);
    end
    k = k + 1;
end

end

