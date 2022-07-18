classdef PushStatus < int32
    enumeration
        Success(0)
        TryAgain(1)
        Finished(2)
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end