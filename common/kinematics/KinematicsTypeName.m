classdef ( Sealed ) KinematicsTypeName < handle
    properties ( Constant )
        KinType     = 'xyzbc';
        KIN_PRE_FIX = 'kin';
    end
    methods (Static)
        function singleObj = get_instance
            persistent localObj
            if isempty(localObj) || ~isvalid(localObj)
                localObj = StructTypeName;
            end
            singleObj = localObj;
        end
        function [ name ] = get_fun_name( fun )
            name = KinematicsTypeName.KIN_PRE_FIX   + "_" + ...
                KinematicsTypeName.toString( fun )  + "_" + ...
                KinematicsTypeName.KinType;

        end
        function [ list ] = get_all_fun_name()
            fun     = enumeration( KinFunctionName.MGD );
            N       = length( fun );
            list    = cell( N, 1 );
            for j = 1 : N
                list{ j } = KinematicsTypeName.get_fun_name( fun( j ) );
            end
        end
        function [ s ] = toString( fun )
            switch( fun )
                case KinFunctionName.MGI
                    s = "inverse";
                case KinFunctionName.MGD
                    s = "forward";
                otherwise
                    s = string( fun );
            end
        end
    end

end