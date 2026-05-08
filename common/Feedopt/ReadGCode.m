function [ status, CurvStruct, err_msg ] = ReadGCode( cfg, cmd, filename )
%#codegen
% ReadGCode : G-code 文件读取器（包装层）
% 在 MATLAB 模式下通过 MEX 调用 C++ 解释器（rs274ngc），
% 在代码生成模式下直接嵌入 C++ 源码（cpp_interp.cpp）。
%
% 工作流程（两次调用）：
%   第一次调用：cmd = ReadGCodeCmd.Load → 打开并初始化 G-code 解释器
%   后续调用：  cmd = ReadGCodeCmd.Read → 每次读取并返回一条曲线段
%
% Inputs :
%   cfg      : 配置结构体（含 ENABLE_PRINT_MSG 等）
%   cmd      : 操作命令（ReadGCodeCmd.Load 或 ReadGCodeCmd.Read）
%   filename : G-code 文件路径（.ngc 或 .mat）
%
% Outputs :
%   status     : 当前读取状态码（见 ReadGCodeError）
%   CurvStruct : 解析出的曲线段结构体
%   err_msg    : 错误信息结构体
%

% persistent 变量在多次调用间保持状态（用于 .mat 文件的批量读取）
persistent n data using_mat
status          = ReadGCodeError.InterpError; % 默认为错误状态
CurvStruct      = constrCurvStructType;       % 初始化空曲线结构体
err_msg         = constrMsgStructType;        % 初始化空错误信息

if coder.target('matlab')
    % ----------------------------------------------------------------
    % MATLAB 模式：通过 MEX 文件调用 C++ G-code 解释器
    % ----------------------------------------------------------------
    if cmd == ReadGCodeCmd.Load
        % 设置配置文件路径（机床参数，如轴限制、换刀参数等）
        setenv( "INI_FILE_NAME", pwd + "/config.ini" );
        ocn_print( cfg.ENABLE_PRINT_MSG, ...
            "The configuration file is located : " + ...
            getenv("INI_FILE_NAME"), mfilename );
        ext = filename( end-3 : end ); % 获取文件扩展名

        ocn_print( cfg.ENABLE_PRINT_MSG, "Filename : " + filename, mfilename );
        if ext == ".mat"
            % .mat 文件模式：从预先保存的 CurvStructs 表加载（用于调试回放）
            ocn_print( cfg.ENABLE_PRINT_MSG, 'Loading CurvStructs ...', mfilename );
            data = load( filename, 'CurvStructs' );
            data = table2struct( data.CurvStructs );
            ocn_print( cfg.ENABLE_PRINT_MSG, 'Done', mfilename );
            using_mat = true;
            n = 1;
            status = ~isempty( data ); % 非空则返回 true（成功）
        else
            % .ngc 文件模式：调用 MEX 初始化 C++ 解释器
            using_mat = false;
            [status, CurvStruct, err_msg] = ReadGCode_mex( 'ReadGCode', ...
                cfg, cmd, filename);
        end
    elseif cmd == ReadGCodeCmd.Read
        if using_mat
            % .mat 批量读取模式：逐条返回预加载的曲线
            if n < length( data )
                CurvStruct = data( n );
                n = n + 1;
                status = 1; % 1 = 继续读取
            else
                status = 0; % 0 = 读取完毕
                CurvStruct = data( 1 );
            end
        else
            % .ngc 模式：调用 MEX 逐条解析下一条 G-code 指令
            [ status, CurvStruct, err_msg ] = ReadGCode_mex( 'ReadGCode', ...
                cfg, cmd, filename );
        end
    end
else
    % ----------------------------------------------------------------
    % 代码生成模式：直接将 C++ 源码编译进生成代码
    % ----------------------------------------------------------------
    coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')

    my_path = StructTypeName.WDIR + "/src";
    coder.updateBuildInfo('addIncludePaths', my_path);

    % rs274ngc 是 LinuxCNC 的开源 G-code 解释器，本项目借用其解析器
    pathRs274Src = StructTypeName.WDIR + "/../../rs274ngc/src";
    coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
    % 将 rs274ngc 解释器的所有 .cc/.cpp 源文件加入编译
    coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp', my_path);
    coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','rotational_axis_mode.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_arc.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_array.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_base.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_check.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_convert.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_cycles.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_execute.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_find.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_internal.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_o_word.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_queue.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_read.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_remap.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_setup.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','interp_write.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','ocn.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc', pathRs274Src);
    coder.updateBuildInfo('addSourceFiles','inifile.cc', pathRs274Src);
    coder.updateBuildInfo('addLinkFlags', '-ldl'); % 动态链接库标志
    coder.cinclude('cpp_interp.hpp');              % 包含 C++ 接口头文件

    switch cmd
        case ReadGCodeCmd.Load
            % 调用 C++ 函数初始化解释器，传入文件名（以 null 终止）
            status = coder.ceval( 'cpp_interp_init', [filename 0], coder.ref(err_msg) );
        case ReadGCodeCmd.Read
            is_loaded = false;
            is_loaded = coder.ceval( 'cpp_interp_loaded', coder.ref(err_msg) );
            if is_loaded
                % 调用 C++ 函数读取下一条指令，填充 CurvStruct
                status  = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct ), coder.ref(err_msg) );
            else
                status  = ReadGCodeError.InterpError;
            end
    end
end

% 调试开关（if(0) 永远不执行，需要时改为 if(1)）
if(0)
    fprintf(1, "[%d]%s\n", int32(status),"[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
    err_msg.msg);
end

% 断言：status 必须小于 InterpNotOpen（即解释器已正常启动）
ocn_assert( status < ReadGCodeError.InterpNotOpen, ...
    "[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
    err_msg.msg( 1 : err_msg.size ), mfilename );

end
