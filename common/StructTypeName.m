classdef ( Sealed ) StructTypeName < handle
    properties ( Constant )
        BaseSpline = 'BaseSplineStruct';
        Curve      = 'CurvStruct';
        Spline     = 'SplineStruct';
        GCodeInfo  = 'GcodeInfoStruct';
        FeedoptCtx = 'FeedoptContext';
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
        dimR        = { [ 6, 1 ], [ 0, 0 ] };
        % Default size for the polynom used for the transition
        dimCoeffP5  = { [ Inf, 6 ], [ 1, 0 ] };
        % Default size for the coefficient of the optimization
        dimCoeffOpt = { [Inf, 1], [1, 0] };
        % Default size for the vector of angles
        dimADeg     = { [Inf, 1], [1, 0] };
        % Default size for the b-spline basis
        dimBasis    = { [Inf, Inf], [1, 1] };
        dimBasisInt = { [Inf, 1],   [1, 0] };
        % Default size for uvec in ctx
        dimCtxUvec  = { [1, Inf], [0, 1] };
        % Default size for Coeff in ctx
        dimCtxCoeff = { [1, Inf], [0, 1] };
        % Default size for breakpoints in Bl in ctx
        dimCtxBlBreaks = { [1, Inf], [0, 1] };
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