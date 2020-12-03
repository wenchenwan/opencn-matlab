classdef DebugCfg < int32
    enumeration
        Transitions(1),
        OptimProgress(2),
        FeedratePlanning(3),
        Global(4),
        Warning(5),
        Error(6),
        Plots(7),
        Validate(8)
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end