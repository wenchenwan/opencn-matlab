classdef ZSpdMode < int32
    enumeration
        NN(0),
        ZN(1),
        NZ(2),
        ZZ(3)
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end