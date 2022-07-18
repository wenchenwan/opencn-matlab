classdef ReadGCodeCmd < int32
        enumeration 
            Load(1), 
            Read(2)
        end
        
        methods(Static)
            function value = addClassNameToEnumNames()
                value = true;
            end
        end
end