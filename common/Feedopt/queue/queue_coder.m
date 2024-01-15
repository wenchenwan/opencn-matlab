classdef queue_coder %#codegen
% queue_coder : A class that represents a queue
    properties ( SetAccess = private )
        ptr uint64      % Handle to the queue pointer
        value_type      % Value type
    end
    
    methods ( Access = public )
        function [ this ] = queue_coder( value_type )
            % queue_coder : Class constructor
            coder.inline( "never" );
            this.value_type = value_type;
            this.ptr        = queue_new();
        end
        
        function push( this, value )
            % push : Push the new element in the queue
            coder.inline( "never" );
            queue_push( this.ptr, value );
        end
        
        function [ value ] = get( this, index )
            % get : Get the element at a given index from the queue
            coder.inline("never");
            value = queue_get( this.ptr, this.value_type, index );
        end
        
        function set(this, index, value)
            % set : Set the element at a given index in the queue
            coder.inline("never");
            queue_set( this.ptr, index, value );
        end
        
        function [ value ] = rget(this, index)
            % rget : Reverse get the element from the queue
            coder.inline("never");
            value = this.get( this.size - index + 1 );
        end
        
        function [ value ] = size( this )
            % size : Get the queue size
            coder.inline("never");
            value = queue_size( this.ptr );
        end
        
        function [ value ] = isempty( this )
            % isempty : Return emptiness of the queue
            coder.inline("never");
            value = (this.size() == 0);
        end
        
        function [ values ] = getall( this )
            % getall : Return of the elements in the queue
            coder.inline("never");
            values = queue_get_all( this.ptr );
        end
        
        function delete( this )
            % delete : Delete the elements of the queue
            coder.inline("never");
            queue_delete( this.ptr );
        end
    end
end
