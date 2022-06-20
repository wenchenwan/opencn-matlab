classdef Kinematics
    % Kinematics :
    %  Wrapper class used to call the C interfaces for the kinematics
    %#codegen
    properties ( SetAccess = private )
        type                % Kinematics type
        parameters          % Kinematics paramters
    end

    methods ( Access = public )

        %----------------------------------------------------------------%
        % Kinematics Wrapper class to C interfaces
        %----------------------------------------------------------------%

        function [ this ] = Kinematics( type, parameters )
            this.type       = type;
            this.parameters = parameters( : );
            [ this ] = set_function_ptr( this );
        end

        function [ this ] = set_params( this, parameters )
            this.parameters = parameters( : );
        end

        function [ this ] = set_type( this, type )
            this.type = type;
        end

        function [ params ] = get_params( this )
            params = this.parameters;
        end

        function [ type ] = get_type( this )
            type = this.type;
        end

        %----------------------------------------------------------------%
        % Basic kinematics
        %----------------------------------------------------------------%
        function [ r_r ] = r_relative( this, r_a )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_a, 2 );
                r_r = zeros( size( r_a ) );
                for j = 1 : N
                    r_r( :, j ) = kin_forward_xyzbc( r_a( : , j ), this.parameters );
                end
%             end
        end

        function [ r_a ] = r_joint( this, r_r )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_r, 2 );
                r_a = zeros( size( r_r ) );
                for j = 1 : N
                    r_a( :, j ) = kin_inverse_xyzbc( r_r( : , j ), this.parameters );
                end
%             end
        end

        %----------------------------------------------------------------%
        % Advanced kinematics
        %----------------------------------------------------------------%
        %% All
        function [ r_r, v_r, a_r, j_r ] = relative( this, r_a, v_a, a_a, j_a )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_a, 2 );
                r_r = zeros( size( r_a ) );
                v_r = zeros( size( v_a ) );
                a_r = zeros( size( a_a ) );
                j_r = zeros( size( j_a ) );

                for j = 1 : N
                    J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
                    JP  = kin_JP_ra_xyzbc( r_a( :, j ), v_a( :, j ), this.parameters );
                    J2P = kin_J2P_ra_xyzbc( r_a( :, j ), v_a( :, j ), a_a( :, j ), this.parameters );
                    r_r( :, j ) = kin_forward_xyzbc( r_a( :, j ), this.parameters );
                    v_r( :, j ) = J * v_a( :, j );
                    a_r( :, j ) = JP * v_a( :, j )  + J * a_a( :, j );
                    j_r( :, j ) = J2P * v_a( :, j ) + 2 * JP * a_a( :, j ) + J * j_a( :, j );
                end
%             end
        end

        function [ r_a, v_a, a_a, j_a ] = joint( this, r_r, v_r, a_r, j_r )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_r, 2 );
                r_a = zeros( size( r_r ) );
                v_a = zeros( size( v_r ) );
                a_a = zeros( size( a_r ) );
                j_a = zeros( size( j_r ) );

                for j = 1 : N
                    J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
                    JP  = kin_JP_ar_xyzbc( r_r( :, j ), v_r( :, j ), this.parameters );
                    J2P = kin_J2P_ar_xyzbc( r_r( :, j ), v_r( :, j ), a_r( :, j ), this.parameters );
                    r_a( :, j ) = kin_inverse_xyzbc( r_r( :, j ), this.parameters );
                    v_a( :, j ) = J * v_r( :, j );
                    a_a( :, j ) = JP * v_r( :, j ) + J * a_r( :, j );
                    j_a( :, j ) = J2P * v_r( :, j ) + 2 * JP * a_r( :, j ) + J * j_r( :, j );
                end
%             end
        end

        %% Jacobian
        function [ v_r ] = v_relative( this, r_a, v_a )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_a, 2 );
                v_r = zeros( size( v_a ) );
                for j = 1 : N
                    J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
                    v_r( :, j ) = J * v_a( :, j );
                end
%             end
        end

        function [ v_a ] = v_joint( this, r_r, v_r )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_r, 2 );
                v_a = zeros( size( v_r ) );

                for j = 1 : N
                    J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
                    v_a( :, j ) = J * v_r( :, j );
                end
%             end
        end

        %% Jacobian - First derivative
        function [ a_r ] = a_relative( this, r_a, v_a, a_a )
            N   = size( r_a, 2 );
            a_r = zeros( size( a_a ) );

            for j = 1 : N
                J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
                JP  = kin_JP_ra_xyzbc( r_a( :, j ), v_a( :, j ), this.parameters );
                a_r( :, j ) = JP * v_a( :, j ) + J * a_a( :, j );
            end
        end

        function [ a_a ] = a_joint( this, r_r, v_r, a_r )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_r, 2 );
                a_a = zeros( size( a_r ) );

                for j = 1 : N
                    J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
                    JP  = kin_JP_ar_xyzbc( r_r( :, j ), v_r( :, j ), this.parameters );
                    a_a( :, j ) = JP * v_r( :, j ) + J * a_r( :, j );
                end
%             end
        end

        %% Jacobian - Second derivative
        function [ j_r ] = j_relative( this, r_a, v_a, a_a, j_a )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_a, 2 );
                j_r = zeros( size( j_a ) );

                for j = 1 : N
                    J   = kin_J_ra_xyzbc( r_a( :, j ), this.parameters );
                    JP  = kin_JP_ra_xyzbc( r_a( :, j ), v_a( :, j ), this.parameters );
                    J2P = kin_J2P_ra_xyzbc( r_a( :, j ), v_a( :, j ), a_a( :, j ), this.parameters );
                    j_r( :, j ) = J2P * v_a( :, j ) + 2 * JP * a_a( :, j ) + J * j_a( :, j );
                end
%             end
        end

        function [ j_a ] = j_joint( this, r_r, v_r, a_r, j_r )
%             if( coder.target( 'MATLAB' ) )
                N   = size( r_r, 2 );
                j_a = zeros( size( j_r ) );

                for j = 1 : N
                    J   = kin_J_ar_xyzbc( r_r( :, j ), this.parameters );
                    JP  = kin_JP_ar_xyzbc( r_r( :, j ), v_r( :, j ), this.parameters );
                    J2P = kin_J2P_ar_xyzbc( r_r( :, j ), v_r( :, j ), a_r( :, j ), this.parameters );
                    j_a( :, j ) = J2P * v_r( :, j ) + 2 * JP * a_r( :, j ) + J * j_r( :, j );
                end
%             end
        end

        %----------------------------------------------------------------%
        % Support for different kinematics only for matlab flow
        %----------------------------------------------------------------%

        function [ this ] = set_function_ptr( this )
            % Not implemented due to problem of support in code
            % generation...
        end
    end

end