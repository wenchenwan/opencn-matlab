classdef ReadGCodeError < int32
    enumeration
    InterpOk(0)
    InterpExit(1)
    InterpExecEnd(2)
    InterpEndFile(3)
    InterpNotOpen(4)
    InterpError(5)
    ToDebug(6)
    end
    
    methods(Static)
        function value = addClassNameToEnumNames()
            value = true;
        end
    end
end