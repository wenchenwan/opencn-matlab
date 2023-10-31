classdef Kinematics
    % Kinematics :
    %  Wrapper class used to call the C interfaces for the kinematics
    %#codegen
    properties ( SetAccess = private )
        type                % Kinematics type
        parameters          % Kinematics paramters
        indM                % Index Machine Offset
        indT                % Tool  Machine Offset
        indP                % Piece Machine Offset
    end

    methods ( Access = private )
        function [ this ] = set_index( this )
            ind     = [ 1 : 3 ];
            this.indM    = ind + 0;
            this.indT    = ind + this.indM(end);
            this.indP    = ind + this.indT(end);
        end
    end

    methods ( Access = public )

        %----------------------------------------------------------------%
        % Kinematics Wrapper class to C interfaces
        %----------------------------------------------------------------%

        function [ this ] = Kinematics( type, parameters )
            coder.inline( "never" );
            this            = this.set_index();
            this.type       = type;
            this.parameters = parameters( : );
            [ this ]        = set_function_ptr( this );
        end

        function [ this ] = set_params( this, parameters )
            coder.inline( "never" );
            this.parameters = parameters( : );
        end

        function [ this ] = set_type( this, type )
            coder.inline( "never" );
            this.type = type;
        end

        function [ this ] = set_machine_offset( this, offset )
            coder.inline( "never" );
            this.parameters(this.indM) = offset;
        end

        function [ this ] = set_tool_offset( this, offset )
            coder.inline( "never" );
            this.parameters(this.indT) = offset;
        end

        function [ this ] = set_piece_offset( this, offset )
            coder.inline( "never" );
            this.parameters(this.indP) = offset;
        end

        function [ this ] = set_tool_length( this, tool_length )
            coder.inline( "never" );
            this.parameters(this.indT(end)) = tool_length;
        end

        function [ params ] = get_params( this )
            coder.inline( "never" );
            params = this.parameters;
        end

        function [ type ] = get_type( this )
            coder.inline( "never" );
            type = this.type;
        end

        %----------------------------------------------------------------%
        % Basic kinematics
        %----------------------------------------------------------------%
        function [ r_t ] = r_relative( this, r_j )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_j, 2 );
            r_t = zeros( size( r_j ) );
            for j = 1 : N
                r_t( :, j ) = kin_xyzbc_tt_forward( r_j( : , j ), this.parameters );
            end
            %             end
        end

        function [ r_j ] = r_joint( this, r_t )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_t, 2 );
            r_j = zeros( size( r_t ) );
            for j = 1 : N
                r_j( :, j ) = kin_xyzbc_tt_inverse( r_t( : , j ), this.parameters );
            end
            %             end
        end

        %----------------------------------------------------------------%
        % Advanced kinematics
        %----------------------------------------------------------------%
        %% All
        function [ r_t, v_t, a_t, j_t ] = relative( this, r_j, v_j, a_j, j_j )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_j, 2 );
            r_t = zeros( size( r_j ) );
            v_t = zeros( size( v_j ) );
            a_t = zeros( size( a_j ) );
            j_t = zeros( size( j_j ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters );
                J2P = kin_xyzbc_tt_J2P_tj( r_j( :, j ), v_j( :, j ), a_j( :, j ), this.parameters );
                r_t( :, j ) = kin_xyzbc_tt_forward( r_j( :, j ), this.parameters );
                v_t( :, j ) = J * v_j( :, j );
                a_t( :, j ) = JP * v_j( :, j )  + J * a_j( :, j );
                j_t( :, j ) = J2P * v_j( :, j ) + 2 * JP * a_j( :, j ) + J * j_j( :, j );
            end
            %             end
        end

        function [ r_j, v_j, a_j, j_j ] = joint( this, r_t, v_t, a_t, j_t )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_t, 2 );
            r_j = zeros( size( r_t ) );
            v_j = zeros( size( v_t ) );
            a_j = zeros( size( a_t ) );
            j_j = zeros( size( j_t ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
                J2P = kin_xyzbc_tt_J2P_jt( r_t( :, j ), v_t( :, j ), a_t( :, j ), this.parameters );
                r_j( :, j ) = kin_xyzbc_tt_inverse( r_t( :, j ), this.parameters );
                v_j( :, j ) = J * v_t( :, j );
                a_j( :, j ) = JP * v_t( :, j ) + J * a_t( :, j );
                j_j( :, j ) = J2P * v_t( :, j ) + 2 * JP * a_t( :, j ) + J * j_t( :, j );
            end
            %             end
        end

        %% Jacobian
        function [ v_t ] = v_relative( this, r_j, v_j )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_j, 2 );
            v_t = zeros( size( v_j ) );
            for j = 1 : N
                J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
                v_t( :, j ) = J * v_j( :, j );
            end
            %             end
        end

        function [ v_j ] = v_joint( this, r_t, v_t )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_t, 2 );
            v_j = zeros( size( v_t ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
                v_j( :, j ) = J * v_t( :, j );
            end
            %             end
        end

        %% Jacobian - First derivative
        function [ a_t ] = a_relative( this, r_j, v_j, a_j )
            coder.inline( "never" );

            N   = size( r_j, 2 );
            a_t = zeros( size( a_j ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters );
                a_t( :, j ) = JP * v_j( :, j ) + J * a_j( :, j );
            end
        end

        function [ a_j ] = a_joint( this, r_t, v_t, a_t )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_t, 2 );
            a_j = zeros( size( a_t ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
                a_j( :, j ) = JP * v_t( :, j ) + J * a_t( :, j );
            end
            %             end
        end

        %% Jacobian - Second derivative
        function [ j_t ] = j_relative( this, r_j, v_j, a_j, j_j )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_j, 2 );
            j_t = zeros( size( j_j ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters );
                J2P = kin_xyzbc_tt_J2P_tj( r_j( :, j ), v_j( :, j ), a_j( :, j ), this.parameters );
                j_t( :, j ) = J2P * v_j( :, j ) + 2 * JP * a_j( :, j ) + J * j_j( :, j );
            end
            %             end
        end

        function [ j_j ] = j_joint( this, r_t, v_t, a_t, j_t )
            coder.inline( "never" );

            %             if( coder.target( 'MATLAB' ) )
            N   = size( r_t, 2 );
            j_j = zeros( size( j_t ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
                J2P = kin_xyzbc_tt_J2P_jt( r_t( :, j ), v_t( :, j ), a_t( :, j ), this.parameters );
                j_j( :, j ) = J2P * v_t( :, j ) + 2 * JP * a_t( :, j ) + J * j_t( :, j );
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