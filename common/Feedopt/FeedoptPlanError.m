classdef FeedoptPlanError < int32
    enumeration
        NoError(0)
        ReadGCodeFailed(1)
        CuspFailed(2)
        CompressingFailed(3)
        SmoothingFailed(4)
        SplittingFailed(5)
        OptimizationFailed(6)
        Success(7)
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end