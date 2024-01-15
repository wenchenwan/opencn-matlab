classdef AngleMode < int32 
    %#codegen
    % AngleMode : Enumeration used to describe the direction of the
    % rotation when the Din norm is enable and the Mode G90 is activated.
    enumeration
        CW(0),          % Turns clockwise ( '+' )
        CCW(1),         % Turns counterclockwise ( '-' )
        Closest(2),     % Go to the closest ( No sign is given )
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end
