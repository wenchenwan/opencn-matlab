classdef (Sealed) DebugOptimization < handle
    properties
        dir_path        string;
        save_data       logical;
        list_file_name;
    end

    properties (Constant)
        test_file_path = "dev/test_debug_optimization.m";
    end

    methods (Static, Access = private)

        function obj = new_instance( dir_path )
            obj.dir_path        = dir_path;
            obj.save_data       = true;
            obj.list_file_name  = [];
        end

        function obj = new_default_instance()
            obj.dir_path        = "";
            obj.save_data       = false;
            obj.list_file_name  = [];
        end

        function obj = instance( mode, obj )
            persistent localObj;
            
            switch ( mode )
                case DebugOptimization.GET
                %
                case DebugOptimization.INIT
                %
                localObj = DebugOptimization.new_default_instance();
                case DebugOptimization.RESET
                %
                localObj = DebugOptimization.new_default_instance();
                case DebugOptimization.SET
                %
                localObj = obj;
                otherwise
                    error("Mode not supported...");
            end

            if ( isempty(localObj) )
                localObj = DebugOptimization.new_default_instance();
            end
            obj = localObj;
        end
    end

    methods (Static)
        function init( dir_path )
            if( nargin == 0 )
                DebugOptimization.instance( DebugOptimization.INIT );
            elseif( nargin == 1 )
                obj = DebugOptimization.new_instance( dir_path );                
                DebugOptimization.instance( DebugOptimization.SET, obj );
            else 
                error("Not supported...");
            end
        end

        function [ obj ] = get()
            obj = DebugOptimization.instance( DebugOptimization.GET );
        end

        function [ dir_path ] = get_dir_path()
            obj = DebugOptimization.instance( DebugOptimization.GET );
            dir_path = obj.dir_path;
        end

        function [ list_file_name ] = get_list_file_name()
            obj = DebugOptimization.instance( DebugOptimization.GET );
            list_file_name = obj.list_file_name;
        end
    
        function [ file_name ] = add_file_name( source, k )
            temp      = string( source ).split("/");
            temp      = temp(end).split(".ngc");
            file_name = temp(1) + "_opt_failled_k_" + k;
            obj = DebugOptimization.instance( DebugOptimization.GET );
            obj.list_file_name = [ obj.list_file_name; file_name ];
            DebugOptimization.instance( DebugOptimization.SET, obj );
        end
            
        function reset()
            DebugOptimization.instance( DebugOptimization.RESET );
        end

        function [ save_data ] = save_opt_data()
            obj = DebugOptimization.instance( DebugOptimization.GET );
            save_data = obj.save_data;
        end

        function set_dir_path( dir_path )
            obj = DebugOptimization.instance( DebugOptimization.GET );
            obj.dir_path = dir_path;
            DebugOptimization.instance( DebugOptimization.SET, obj );
        end

        function set_save_data( save_data )
            obj = DebugOptimization.instance( DebugOptimization.GET );
            obj.save_data = save_data;
            DebugOptimization.instance( DebugOptimization.SET, obj );
        end
    end

    enumeration (Hidden)
        GET, INIT, RESET, SET
    end
end