function [ ctx ] = compressCurvStructs( ctx )
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

if ctx.q_gcode.isempty(), return; end

spline_index        = ctx.q_spline.size() + 1;  % New index in q_spline
Length_Threshold    = ctx.cfg.LThreshold;       % in [mm]
Ncrv    = ctx.q_gcode.size;                     % Number of curve in queue

% Vector for the speed mode of the first and the last segment of the spline
zspdmodevec = [ ZSpdMode.NN, ZSpdMode.NN ];

CumulatedLength = 0;                       % Accumulator for the length
spindle_speed   = 75000;                   % in [rpm]

DebugLog(DebugCfg.Validate, 'Compressing...\n');

% Satisfy coder
if ( ~ coder.target( 'MATLAB' ) )
    pvec    = zeros( 6, 1 );
    coder.varsize( 'pvec', [ 6, Inf ], [0, 1] );
end

for k = 1 : Ncrv
    curve = ctx.q_gcode.get(k);          % Get next Curv in the queue
    % If the next curve segment is too long for compressing or it is not an NN,
    % we need to stop growing the compressing list and create the spline

    if k > 1      % Check colinearity with previous segment
        preCurve    = ctx.q_gcode.get( k-1 );
        Collinear   = curvCollinear(ctx, preCurve, curve, ...
            ctx.cfg.Compressing.ColTolCosLee);
    else % Set default value for the c code generation
        preCurve    = curve;
        Collinear   = false;
    end

    % A new spline is created if one of the following conditions is met :
    %  - The length of the current curve is too long for the compressing
    %  - One of the boundaries speed is zero
    % No more segment is added to the list of compressing curves
    if ( curve.Info.Type ~= CurveType.Line )        || ... % Not a Line
            ( curve.Info.zspdmode == ZSpdMode.NZ )       || ... % Zero stop
            ( (k ~= 1)  && ~Collinear )                  || ... % Not collinear and not 1rst segment
            ( (k == Ncrv) && (CumulatedLength ~= 0) )    || ... % Last segment and on-going compression
            ( LengthCurv(ctx, curve, 0, 1) >= Length_Threshold ) % Too long segment

        % In this case add the last segment
        if ( ( isAZeroEnd( curve ) ) || ... % Zero stop OR Last segment
                ( k == Ncrv ) ) && ( CumulatedLength ~= 0 ) % AND on-going compression
            pvec = [ pvec curve.R1 ];
            zspdmodevec( end ) =  curve.Info.zspdmode;
            spindle_speed = min( spindle_speed, curve.Info.SpindleSpeed );
        end


        % If the cumulated length is zero, no compressing is on-going.
        % The segment is treated individually
        if ( CumulatedLength == 0 )
            ctx.q_compress.push( curve );

            % If there was an on-going compression
        else
            % We have more than 2 points, thus constructing a spline
            % is warranted
            if ( size( pvec, 2 ) > 2 )
                splineCurve             = constrCurvStructType;
                splineCurve.Info.Type   = CurveType.Spline;
                splineCurve.sp_index    = spline_index;
                splineCurve.sp          = CalcBspline_Lee( ctx.cfg, pvec( ctx.cfg.indTot, : ) );
                [Ltot, Lk]              = SplineLengthApproxGL_tot( ctx, splineCurve );
                splineCurve.sp.Ltot     = Ltot;
                splineCurve.sp.Lk       = Lk;

                spline = constrSplineStruct( curve.Info, pvec(:,1), ...
                    pvec(:,end), uint32( spline_index ) );

                % Calculate the ZSpdMode for the spline
                first   = zspdmodevec( 1 );
                last    = zspdmodevec( end );

                if ( first == ZSpdMode.NN ) && ( last == ZSpdMode.NN )
                    spline.Info.zspdmode = ZSpdMode.NN;
                elseif  ( first == ZSpdMode.NN ) && ( last == ZSpdMode.NZ )
                    spline.Info.zspdmode = ZSpdMode.NZ;
                elseif  ( first == ZSpdMode.ZN ) && ( last == ZSpdMode.NN )
                    spline.Info.zspdmode = ZSpdMode.ZN;
                elseif ( first == ZSpdMode.ZN ) && ( last == ZSpdMode.NZ )
                    spline.Info.zspdmode = ZSpdMode.ZZ;
                else
                    fprintf('ERROR IN ZSPDMODE');
                end

                ctx.q_spline.push( splineCurve );
                ctx.q_compress.push( spline );

                spline_index = spline_index + 1;

                % With only two points, construct a line
            else
                ctx.q_compress.push( preCurve ); % push segment to q_compress
                ctx.q_compress.push( curve );    % push segment to q_compress
            end
            CumulatedLength = 0;
        end
        % In the general case with an elligible segment, add it to the
        % compression list
    else
        if CumulatedLength == 0
            pvec    = curve.R0;
            spindle_speed   = curve.Info.SpindleSpeed;
            zspdmodevec( 1 )= curve.Info.zspdmode;
        end

        CumulatedLength = CumulatedLength + LengthCurv( ctx, curve, 0, 1 );
        pvec    = [pvec curve.R1];
        zspdmodevec( end ) = curve.Info.zspdmode;
        spindle_speed = min( spindle_speed, curve.Info.SpindleSpeed );
    end
end
end

