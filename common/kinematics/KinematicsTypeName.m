classdef ( Sealed ) KinematicsTypeName < handle
    properties ( Constant )
        KinType     = 'xyzbc_tt';
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
                KinematicsTypeName.KinType          + "_" + ...
                KinematicsTypeName.toString( fun );

        end
        function [ list ] = get_all_fun_name()
            fun     = enumeration( KinFunctionName.Forward );
            N       = length( fun );
            list    = cell( N, 1 );
            for j = 1 : N
                list{ j } = KinematicsTypeName.get_fun_name( fun( j ) );
            end
        end
        function [ s ] = toString( fun )
            switch( fun )
                case KinFunctionName.Forward
                    s = "forward";
                case KinFunctionName.Inverse
                    s = "inverse";
                case KinFunctionName.Forward_complete
                    s = "forward_complete";
                case KinFunctionName.Inverse_complete
                    s = "inverse_complete";
                case KinFunctionName.Inverse_angle
                    s = "inverse_angle";
                otherwise
                    s = string( fun );
            end
        end
        function [params] = varTypeKinematic( kinType )
        % VarTypeKinematic
        % Define type of variable necessary for kinematics functions
        
            R = double( zeros( 5, 1 ) );
            P = double( zeros( 3, 5 ) );
            switch kinType
            case KinFunctionName.Forward
                params = {R, P};
            case KinFunctionName.Inverse
                params = {R, P};
            case KinFunctionName.J_jt
                params = {R, P};
            case KinFunctionName.J_tj
                params = {R, P};
            case KinFunctionName.JP_jt
                params = {R, R, P};
            case KinFunctionName.JP_tj
                params = {R, R, P};
            case KinFunctionName.J2P_jt
                params = {R, R, R, P};
            case KinFunctionName.J2P_tj
                params = {R, R, R, P};
            case KinFunctionName.Forward_complete
                params = {R, P};
            case KinFunctionName.Inverse_complete
                params = {double( zeros( 6, 1 ) ), P};
            case KinFunctionName.Inverse_angle
                params = {double( zeros( 3, 1 ) ), P};
            otherwise
                params = {};
            end
        end
    end

end
