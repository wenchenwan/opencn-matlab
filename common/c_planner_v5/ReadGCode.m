function [status, CurvStruct] = ReadGCode(cmd, filename)
%#codegen
% coder.extrinsic('ReadGCode_mex');
% Wrapper for pulling the next gcode line from the interpreter
persistent n data using_mat

if coder.target('mex')
    trafo = false;
    A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;
    CurvStruct = ConstrLineStruct(trafo, [1,2,3]', [4,5,6]', A0, A1, U0, ...
                                    U1, 0.2, ZSpdMode.NN);
    coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
    % coder.updateBuildInfo('addDefines', 'DEBUG_RS274')
    coder.updateBuildInfo('addDefines', 'MEX_READGCODE')
    coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
    coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp', '$(START_DIR)/../common/src');
    coder.updateBuildInfo('addSourceFiles','interp_arc.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_array.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_base.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_check.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_convert.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_cycles.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_execute.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_find.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_internal.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_inverse.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_namedparams.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_o_word.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_queue.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_read.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_remap.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_setup.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','interp_write.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','ocn.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','rs274ngc_pre.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addSourceFiles','inifile.cc', '$(START_DIR)/../../rs274ngc');
    coder.updateBuildInfo('addLinkFlags', '-ldl');
    coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
    coder.cinclude('cpp_interp.hpp');
    
    status = int32(0);
    switch cmd
        case ReadGCodeCmd.Load
            status = coder.ceval('cpp_interp_init', [filename 0]);
        case ReadGCodeCmd.Read
            is_loaded = int32(0);
            is_loaded = coder.ceval('cpp_interp_loaded');
            if is_loaded
                status = coder.ceval('cpp_interp_read', coder.ref(CurvStruct));
            else
                status = int32(0);
            end
    end
elseif coder.target('matlab') 
    if cmd == ReadGCodeCmd.Load
        ext = filename(end-3:end);
        if ext == ".mat"
            fprintf('Loading CurvStructs ... ')
            data = load(filename, 'CurvStructs');
            data = table2struct(data.CurvStructs);
            fprintf('Done\n')
            using_mat = true;
            n = 1;
            status = ~isempty(data);
        else
            using_mat = false;
            [status, CurvStruct] = ReadGCode_mex('ReadGCode', cmd, filename);
        end
    elseif cmd == ReadGCodeCmd.Read
        if using_mat
            if n < length(data)
                CurvStruct = data(n);
                n = n + 1;
                status = 1;
            else
                status = 0;
                CurvStruct = data(1);
            end
        else
            [status, CurvStruct] = ReadGCode_mex('ReadGCode', cmd, filename);
        end
    end
elseif coder.target('rtw')
    trafo = false;
    A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;
    if cmd == ReadGCodeCmd.Load
        CurvStruct = ConstrLineStruct(false, [1,2,3]', [4,5,6]', A0, A1, ...
                                        U0, U1, 0.2, ZSpdMode.NN);
        status = int32(0);
        status = coder.ceval('c_open_gcode', [filename, 0], coder.ref(CurvStruct));
    elseif cmd == ReadGCodeCmd.Read
        CurvStruct = ConstrLineStruct(false, [1,2,3]', [4,5,6]', A0, A1, ...
                                        U0, U1, 0.2, ZSpdMode.NN);
        status = int32(0);
        status = coder.ceval('c_read_and_exec_gcode', '', coder.ref(CurvStruct));
    end
else
    error('Unknown target');
end

end
