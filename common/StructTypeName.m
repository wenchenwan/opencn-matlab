classdef ( Sealed ) StructTypeName < handle

    properties ( Constant )
        Axes       = 'Axes';
        BaseSpline = 'BaseSplineStruct';
        Curve      = 'CurvStruct';
        FeedoptCtx = 'FeedoptContext';
        FeedoptCfg = 'FeedoptConfig';
        GCodeInfo  = 'GcodeInfoStruct';
        MEX        = 'MEX';
        LPCfg      = 'LPCfg';
        Spline     = 'SplineStruct';
        Tool       = 'Tool';
    end
    
    properties ( Constant )
        % Maximum number of axis
        NumberAxisMax = 6;
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
        dimR        = { [ StructTypeName.NumberAxisMax, 1 ], [ 0, 0 ] };
        % Default size for the polynom used for the transition
        dimCoeffP5  = { [ Inf, StructTypeName.NumberAxisMax ], [ 1, 0 ] };
        % Default size for the coefficient of the optimization
        dimCoeffOpt = { [ Inf, 1 ], [ 1, 0 ] };
        % Default size for the vector of angles
        dimADeg     = { [ 1, 1 ], [ 0, 0 ] };
        % Default size for the b-spline basis
        dimBasis    = { [ Inf, Inf ], [ 1, 1 ] };
        dimBasisInt = { [ Inf, 1 ],   [ 1, 0 ] };
        % Default size for uvec in ctx
        dimCtxUvec  = { [ 1, Inf ], [ 0, 1 ] };
        % Default size for Coeff in ctx
        dimCtxCoeff = { [ Inf, Inf ], [ 1, 1 ] };
        % Default size for breakpoints in Bl in ctx
        dimCtxBlBreaks = { [ 1, Inf ], [ 0, 1 ] };
        % Default size for index vector ( cart and rot )
        dimMask     = { [ 1, StructTypeName.NumberAxisMax ], [ 0, 1 ] };
        % Default size for index vector ( cart or rot )
        dimInd      = { [ 3, 1 ], [ 1, 0 ] };
        % Default size for diagonale matrix
        dimD        = { [ StructTypeName.NumberAxisMax, 1 ], [ 1, 0 ] };
        % Default size for the kinematics parameters
        dimKinParams = { [ 32, 1 ], [ 1, 0 ] };
        % Default size for the Pvec used in compressing
        dimPvec = { [ StructTypeName.NumberAxisMax, Inf ], [0, 1] };
        % Get the working directory 
        WDIR = fileparts(mfilename('fullpath'));
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