classdef ( Sealed ) StructTypeName < handle
    properties ( Constant )
        BaseSpline = 'BaseSplineStruct';
        Curve      = 'CurvStruct';
        Spline     = 'SplineStruct';
        GCodeInfo  = 'GcodeInfoStruct';
        MEX        = 'MEX';
    end
    properties ( Constant )
        % Default size for the breakpoints vector
        dimNBreak   = { [ 1, Inf ], [ 0, 1 ] };   
        % Default size for the Coeff vector
        dimCoeffs   = { [ Inf, Inf ], [ 1, 1 ] };
        % Default size for the knots vector
        dimKnots    = { [1, Inf],   [ 0, 1 ] };
        % Default size for the Length vector for spline
        dimLk       = { [ 1, Inf ],  [ 0, 1 ] };
        % Default size for the Pose ( cart + rot )
        dimR        = { [ Inf, 1 ], [ 1, 0 ] };
        % Default size for the polynom used for the transition
        dimCoeffP5  = { [ Inf, 6 ], [ 1, 0 ] };
        % Default size for the coefficient of the optimization
        dimCoeffOpt = { [Inf, 1], [1, 0] };
        % Default size for the vector of angles
        dimADeg     = { [Inf, 1], [1, 0] };
    end

    methods (Access = private)
        function obj = StructTypeName
        end
    end
    methods (Static)
        function singleObj = getInstance
            persistent localObj
            if isempty(localObj) || ~isvalid(localObj)
                localObj = StructTypeName;
            end
            singleObj = localObj;
        end
    end

end