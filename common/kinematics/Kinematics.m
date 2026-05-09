classdef Kinematics
    % Kinematics : 多轴机床运动学变换包装器类
    %
    % 功能描述：
    %   该类封装了多轴机床的运动学变换功能，提供了关节空间与工具空间之间的
    %   坐标变换、速度变换、加速度变换等。支持五轴机床的正解和逆解变换。
    %
    % 运动学基础概念：
    %   - 关节空间（Joint Space）：电机角度/位置坐标系
    %   - 工具空间（Tool Space）：刀具在工件坐标系中的位置和姿态
    %   - 正解变换（Forward Kinematics）：关节坐标 → 工具坐标
    %   - 逆解变换（Inverse Kinematics）：工具坐标 → 关节坐标
    %   - 雅可比矩阵（Jacobian）：关节速度与工具速度之间的线性变换关系
    %
    % 坐标系定义：
    %   - 机床坐标系（Machine Frame）：机床本体坐标系
    %   - 工件坐标系（Workpiece Frame）：工件固定坐标系
    %   - 工具坐标系（Tool Frame）：刀具尖端坐标系
    %
    %#codegen

    properties ( SetAccess = private )
        type                % 运动学类型（例如：XYZBC_TT 五轴机床类型）
        parameters          % 运动学参数向量（包含机床几何参数、偏移等）
        indM                % 机床偏移参数在parameters中的索引
        indT                % 刀具偏移参数在parameters中的索引
        indP                % 工件偏移参数在parameters中的索引
    end

    methods ( Access = private )
        function [ this ] = set_index( this )
            % 设置参数向量中各偏移量的索引位置
            % 每个偏移量占用3个连续位置（X/Y/Z轴）
            ind     = [ 1 : 3 ];
            this.indM    = ind + 0;                    % 机床偏移：索引1-3
            this.indT    = ind + this.indM(end);       % 刀具偏移：索引4-6
            this.indP    = ind + this.indT(end);       % 工件偏移：索引7-9
        end
    end

    methods ( Access = public )

        %----------------------------------------------------------------%
        % 构造函数和参数设置方法
        %----------------------------------------------------------------%

        function [ this ] = Kinematics( type, parameters )
            % 构造函数：初始化运动学对象
            % type: 运动学类型标识符
            % parameters: 运动学参数向量（机床几何参数、偏移等）
            coder.inline( "never" );
            this            = this.set_index();        % 设置参数索引
            this.type       = type;                    % 设置运动学类型
            this.parameters = parameters( : );         % 存储参数向量
            [ this ]        = set_function_ptr( this ); % 设置函数指针（未实现）
        end

        function [ this ] = set_params( this, parameters )
            % 设置运动学参数
            coder.inline( "never" );
            this.parameters = parameters( : );
        end

        function [ this ] = set_type( this, type )
            % 设置运动学类型
            coder.inline( "never" );
            this.type = type;
        end

        function [ this ] = set_machine_offset( this, offset )
            % 设置机床坐标系偏移量（3×1向量：[X,Y,Z]）
            coder.inline( "never" );
            this.parameters(this.indM) = offset;
        end

        function [ this ] = set_tool_offset( this, offset )
            % 设置刀具坐标系偏移量（3×1向量：[X,Y,Z]）
            coder.inline( "never" );
            this.parameters(this.indT) = offset;
        end

        function [ this ] = set_piece_offset( this, offset )
            % 设置工件坐标系偏移量（3×1向量：[X,Y,Z]）
            coder.inline( "never" );
            this.parameters(this.indP) = offset;
        end

        function [ this ] = set_tool_length( this, tool_length )
            % 设置刀具长度（Z轴方向，用于补偿刀具长度）
            coder.inline( "never" );
            this.parameters(this.indT(end)) = tool_length;
        end

        function [ params ] = get_params( this )
            % 获取当前运动学参数
            coder.inline( "never" );
            params = this.parameters;
        end

        function [ type ] = get_type( this )
            % 获取运动学类型
            coder.inline( "never" );
            type = this.type;
        end

        %----------------------------------------------------------------%
        % 基础运动学变换（位置变换）
        %----------------------------------------------------------------%

        function [ r_t ] = r_relative( this, r_j )
            % 正解变换：关节坐标 → 工具坐标
            %
            % 功能：将关节空间的位置坐标转换为工具空间的位置坐标
            % 输入：r_j - 关节坐标矩阵 [N_axis × N_points]
            % 输出：r_t - 工具坐标矩阵 [N_axis × N_points]
            %
            % 其中 r_t = [X; Y; Z; B; C]：
            %   - X/Y/Z 是工件坐标系中的线位移
            %   - B/C 是两个旋转轴角度（B 轴绕 Y 轴、C 轴绕 Z 轴）
            %
            % 对应的速度 v_t 也是该位姿参数的时间导数：
            %   - 前3个分量为线速度
            %   - 后2个分量为 B/C 角速度（dB/dt、dC/dt），而不是通用的欧拉角速度矢量
            %
            % 变换原理：调用C函数 kin_xyzbc_tt_forward 进行正解计算
            coder.inline( "never" );

            N   = size( r_j, 2 );      % 获取数据点数量
            r_t = zeros( size( r_j ) ); % 预分配输出矩阵
            for j = 1 : N
                % 对每个数据点调用正解变换函数
                r_t( :, j ) = kin_xyzbc_tt_forward( r_j( : , j ), this.parameters );
            end
        end

        function [ r_j ] = r_joint( this, r_t )
            % 逆解变换：工具坐标 → 关节坐标
            %
            % 功能：将工具空间的位置坐标转换为关节空间的位置坐标
            % 输入：r_t - 工具坐标矩阵 [N_axis × N_points]
            % 输出：r_j - 关节坐标矩阵 [N_axis × N_points]
            %
            % 变换原理：调用C函数 kin_xyzbc_tt_inverse 进行逆解计算
            coder.inline( "never" );

            N   = size( r_t, 2 );      % 获取数据点数量
            r_j = zeros( size( r_t ) ); % 预分配输出矩阵
            for j = 1 : N
                % 对每个数据点调用逆解变换函数
                r_j( :, j ) = kin_xyzbc_tt_inverse( r_t( : , j ), this.parameters );
            end
        end

        %----------------------------------------------------------------%
        % 高级运动学变换（包含速度、加速度、加加速度）
        %----------------------------------------------------------------%

        %% 完整变换（位置+速度+加速度+加加速度）
        function [ r_t, v_t, a_t, j_t ] = relative( this, r_j, v_j, a_j, j_j )
            % 正解完整变换：关节空间 → 工具空间（含高阶导数）
            %
            % 功能：同时变换位置、速度、加速度、加加速度
            % 输入：
            %   r_j, v_j, a_j, j_j - 关节空间的位置、速度、加速度、加加速度
            % 输出：
            %   r_t, v_t, a_t, j_t - 工具空间的对应量
            %
            % 变换原理：
            %   位置：正解变换
            %   速度：v_t = J * v_j （雅可比矩阵变换）
            %   加速度：a_t = JP*v_j + J*a_j （含雅可比导数项）
            %   加加速度：j_t = J2P*v_j + 2*JP*a_j + J*j_j （含二阶导数项）
            coder.inline( "never" );

            N   = size( r_j, 2 );
            r_t = zeros( size( r_j ) );
            v_t = zeros( size( v_j ) );
            a_t = zeros( size( a_j ) );
            j_t = zeros( size( j_j ) );

            for j = 1 : N
                % 计算各级雅可比矩阵
                J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );     % 雅可比矩阵
                JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters ); % 雅可比导数
                J2P = kin_xyzbc_tt_J2P_tj( r_j( :, j ), v_j( :, j ), a_j( :, j ), this.parameters ); % 雅可比二阶导数

                % 位置变换（正解）
                r_t( :, j ) = kin_xyzbc_tt_forward( r_j( :, j ), this.parameters );

                % 速度变换：v_t = J * v_j
                v_t( :, j ) = J * v_j( :, j );

                % 加速度变换：a_t = JP*v_j + J*a_j
                a_t( :, j ) = JP * v_j( :, j )  + J * a_j( :, j );

                % 加加速度变换：j_t = J2P*v_j + 2*JP*a_j + J*j_j
                j_t( :, j ) = J2P * v_j( :, j ) + 2 * JP * a_j( :, j ) + J * j_j( :, j );
            end
        end

        function [ r_j, v_j, a_j, j_j ] = joint( this, r_t, v_t, a_t, j_t )
            % 逆解完整变换：工具空间 → 关节空间（含高阶导数）
            %
            % 功能：同时变换位置、速度、加速度、加加速度
            % 输入：
            %   r_t, v_t, a_t, j_t - 工具空间的位置、速度、加速度、加加速度
            % 输出：
            %   r_j, v_j, a_j, j_j - 关节空间的对应量
            %
            % 变换原理：与正解变换对称，使用逆雅可比矩阵
            coder.inline( "never" );

            N   = size( r_t, 2 );
            r_j = zeros( size( r_t ) );
            v_j = zeros( size( v_t ) );
            a_j = zeros( size( a_t ) );
            j_j = zeros( size( j_t ) );

            for j = 1 : N
                % 计算各级雅可比矩阵（工具空间到关节空间）
                J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
                J2P = kin_xyzbc_tt_J2P_jt( r_t( :, j ), v_t( :, j ), a_t( :, j ), this.parameters );

                % 位置变换（逆解）
                r_j( :, j ) = kin_xyzbc_tt_inverse( r_t( :, j ), this.parameters );

                % 速度变换：v_j = J * v_t
                v_j( :, j ) = J * v_t( :, j );

                % 加速度变换：a_j = JP*v_t + J*a_t
                a_j( :, j ) = JP * v_t( :, j ) + J * a_t( :, j );

                % 加加速度变换：j_j = J2P*v_t + 2*JP*a_t + J*j_t
                j_j( :, j ) = J2P * v_t( :, j ) + 2 * JP * a_t( :, j ) + J * j_t( :, j );
            end
        end

        %% 速度变换（仅雅可比矩阵）
        function [ v_t ] = v_relative( this, r_j, v_j )
            % 正解速度变换：关节速度 → 工具速度
            %
            % 变换公式：v_t = J * v_j
            % 其中 J 为雅可比矩阵，将关节速度转换为工具速度
            coder.inline( "never" );

            N   = size( r_j, 2 );
            v_t = zeros( size( v_j ) );
            for j = 1 : N
                J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
                v_t( :, j ) = J * v_j( :, j );
            end
        end

        function [ v_j ] = v_joint( this, r_t, v_t )
            % 逆解速度变换：工具速度 → 关节速度
            %
            % 变换公式：v_j = J * v_t
            % 其中 J 为逆雅可比矩阵
            coder.inline( "never" );

            N   = size( r_t, 2 );
            v_j = zeros( size( v_t ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
                v_j( :, j ) = J * v_t( :, j );
            end
        end

        %% 加速度变换（雅可比矩阵及其一阶导数）
        function [ a_t ] = a_relative( this, r_j, v_j, a_j )
            % 正解加速度变换：关节加速度 → 工具加速度
            %
            % 变换公式：a_t = JP*v_j + J*a_j
            % 其中：
            %   J  - 雅可比矩阵
            %   JP - 雅可比矩阵对时间的导数（位置和速度的函数）
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
            % 逆解加速度变换：工具加速度 → 关节加速度
            %
            % 变换公式：a_j = JP*v_t + J*a_t
            % 使用逆雅可比矩阵及其导数
            coder.inline( "never" );

            N   = size( r_t, 2 );
            a_j = zeros( size( a_t ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
                a_j( :, j ) = JP * v_t( :, j ) + J * a_t( :, j );
            end
        end

        %% 加加速度变换（雅可比矩阵及其二阶导数）
        function [ j_t ] = j_relative( this, r_j, v_j, a_j, j_j )
            % 正解加加速度变换：关节加加速度 → 工具加加速度
            %
            % 变换公式：j_t = J2P*v_j + 2*JP*a_j + J*j_j
            % 其中：
            %   J   - 雅可比矩阵
            %   JP  - 雅可比一阶导数
            %   J2P - 雅可比二阶导数（位置、速度、加速度的函数）
            coder.inline( "never" );

            N   = size( r_j, 2 );
            j_t = zeros( size( j_j ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_tj( r_j( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_tj( r_j( :, j ), v_j( :, j ), this.parameters );
                J2P = kin_xyzbc_tt_J2P_tj( r_j( :, j ), v_j( :, j ), a_j( :, j ), this.parameters );
                j_t( :, j ) = J2P * v_j( :, j ) + 2 * JP * a_j( :, j ) + J * j_j( :, j );
            end
        end

        function [ j_j ] = j_joint( this, r_t, v_t, a_t, j_t )
            % 逆解加加速度变换：工具加加速度 → 关节加加速度
            %
            % 变换公式：j_j = J2P*v_t + 2*JP*a_t + J*j_t
            % 使用逆雅可比矩阵及其高阶导数
            coder.inline( "never" );

            N   = size( r_t, 2 );
            j_j = zeros( size( j_t ) );

            for j = 1 : N
                J   = kin_xyzbc_tt_J_jt( r_t( :, j ), this.parameters );
                JP  = kin_xyzbc_tt_JP_jt( r_t( :, j ), v_t( :, j ), this.parameters );
                J2P = kin_xyzbc_tt_J2P_jt( r_t( :, j ), v_t( :, j ), a_t( :, j ), this.parameters );
                j_j( :, j ) = J2P * v_t( :, j ) + 2 * JP * a_t( :, j ) + J * j_t( :, j );
            end
        end

        %----------------------------------------------------------------%
        % 不同运动学类型的支持（仅MATLAB流程）
        %----------------------------------------------------------------%

        function [ this ] = set_function_ptr( this )
            % 设置函数指针（用于支持不同运动学类型）
            % 由于代码生成问题，此功能暂未实现
            % Not implemented due to problem of support in code generation...
        end
    end

end
