classdef queue_matlab
    properties (SetAccess = private)
        data
        count int32
        value_type
    end
    
    methods (Access = public)
        function this = queue_matlab(value_type)
            value = repmat(value_type, 0, 1);
            coder.varsize('value', [Inf, 1], [1, 0]);
            this.data = value;
            this.value_type = value_type;
            this.count = 0;
        end
        
        function this = push(this, value)
            oldsize = this.size();
            if this.count + 1 > oldsize
                newsize = max([int32(1), min([10000, int32(oldsize*2)])]);
                this.data = [this.data; repmat(this.value_type, newsize - oldsize, 1)];
            end
            this.data(this.count+1) = value;
            this.count = this.count + 1;
        end
        
        function value = get(this, index)
            ocn_assert(~(index > this.count), "Outside of range", mfilename);    
            value = this.data(index);
        end
        
        function this = set(this, index, value)
            this.data(index) = value;
        end
        
        function this = reserve(this, newcapacity)
            oldcapacity = capacity();
            if newcapacity > oldcapacity
                this.data = [this.data; repmat(this.value_type, newcapacity - oldcapacity, 1)];
            end
        end
        
        function value = rget(this, index)
            value = this.data(this.count-index+1);
        end
        
        function value = size(this)
            value = this.count;
        end
        
        function value = capacity(this)
            value = size(this.data, 1);
        end
        
        function value = isempty(this)
            value = (this.size() == 0);
        end
        
        function values = getall(this)
            values = this.data(1:this.count);
        end
    end
end
