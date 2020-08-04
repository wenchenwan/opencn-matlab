classdef TransitionResult < int32
    enumeration
        Ok(0),
        Collinear(1),
        NoSolution(2)
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end