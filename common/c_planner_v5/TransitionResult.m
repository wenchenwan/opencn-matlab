classdef TransitionResult < int32
    % Enumeration class representing the results of the smoothing step
    enumeration
        Ok(0),             % Transition succeed
        Collinear(1),      % No need of a transition, curves are colinear
        NoSolution(2)      % No solutions found...
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end