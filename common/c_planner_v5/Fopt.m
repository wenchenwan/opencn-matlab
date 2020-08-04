classdef Fopt < int32
    enumeration
        Init(0)
        GCode(1)
        Check(2)
        Compress(3)
        Smooth(4)
        Split(5)
        Opt(6)
        Finished(67)
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end
