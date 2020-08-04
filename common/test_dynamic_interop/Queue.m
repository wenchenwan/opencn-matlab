classdef Queue < handle
    % This enumeration is used for reference the queues on the c++ side
    % where the are actually std::vector(s) in an array 
    properties(Constant, Access = public)
        GCode = int32(0)
        Smooth = int32(1)
        Split = int32(2)
        Opt = int32(3)
        COUNT = int32(4)
    end
    
    properties(Access = private)
        CQueueID
        Data
    end
    properties
        Size
    end
    methods
        function obj = Queue(id)
            if coder.target('rtw')
                obj.CQueueID = int32(id);
            else
                obj.Data = [];
            end
        end
        
        function Push(obj, Value)
            if coder.target('rtw')
                coder.ceval('queue_push', obj.CQueueID, Value);
            else
                obj.Data = [obj.Data Value];
            end
        end
        
        function value = Get(obj, k)
            if coder.target('rtw')
                value = 0;
                value = coder.ceval('queue_get', obj.CQueueID, k - 1);
            else
                value = obj.Data(k);
            end
        end
        
        function Set(obj, k, Value)
            if coder.target('rtw')
                coder.ceval('queue_set', obj.CQueueID, k - 1, Value);
            else
                obj.Data(k) = Value;
            end
        end
        
        function v = get.Size(obj)
            if coder.target('rtw')
                v = int32(0);
                v = coder.ceval('queue_size', obj.CQueueID);
            else
                v = length(obj.Data);
            end
        end
    end
end