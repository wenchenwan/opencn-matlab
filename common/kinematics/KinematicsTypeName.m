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
        function [params] = varTypeKinematic( kinType )
        % VarTypeKinematic
        % Define type of variable necessary for kinematics functions
        
            R = double( zeros( 5, 1 ) );
            P = double( zeros( 3, 4 ) );
            switch kinType
            case KinFunctionName.MGD
                params = {R, P};
            case KinFunctionName.MGI
                params = {R, P};
            case KinFunctionName.J_ar
                params = {R, P};
            case KinFunctionName.J_ra
                params = {R, P};
            case KinFunctionName.JP_ar
                params = {R, R, P};
            case KinFunctionName.JP_ra
                params = {R, R, P};
            case KinFunctionName.J2P_ar
                params = {R, R, R, P};
            case KinFunctionName.J2P_ra
                params = {R, R, R, P};              
            otherwise
                params = {};
            end
        end
    end

end