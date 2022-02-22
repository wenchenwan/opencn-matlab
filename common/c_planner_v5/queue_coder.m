classdef queue_coder
    properties (SetAccess = private)
        ptr uint64
        value_type
    end
    
    methods (Access = public)
        function this = queue_coder(value_type)
            coder.inline("never");
            this.value_type = value_type;
            this.ptr = queue_new();
        end
        
        function push(this, value)
            coder.inline("never");
            queue_push(this.ptr, value);
        end
        
        function value = get(this, index)
            coder.inline("never");
            value = queue_get(this.ptr, this.value_type, index);
        end
        
        function set(this, index, value)
            coder.inline("never");
            queue_set(this.ptr, index, value);
        end
        
        function value = rget(this, index)
            coder.inline("never");
            value = this.get(this.size - index + 1);
        end
        
        function value = size(this)
            coder.inline("never");
            value = queue_size(this.ptr);
        end
        
        function value = isempty(this)
            coder.inline("never");
            value = (this.size() == 0);
        end
        
        function values = getall(this)
            coder.inline("never");
            values = queue_get_all(this.ptr);
        end
        
        function delete(this)
            coder.inline("never");
            queue_delete(this.ptr);
        end
    end
end
