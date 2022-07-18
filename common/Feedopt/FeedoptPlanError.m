classdef FeedoptPlanError < int32
    enumeration
        Success(0)
        SmoothingFailed(1)
        SplittingFailed(2)
        OptimizationFailed(3)
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end