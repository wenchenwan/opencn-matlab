function [ status, CurvStruct, err_msg ] = ReadGCode( cmd, filename )
%#codegen
% coder.extrinsic('ReadGCode_mex');
% Wrapper for pulling the next gcode line from the interpreter
persistent n data using_mat
status          = ReadGCodeError.InterpError;
CurvStruct      = constrCurvStructType;
err_msg         = constrMsgStructType;

if coder.target('matlab')
    if cmd == ReadGCodeCmd.Load
        setenv( "INI_FILE_NAME", pwd + "/config.ini" );
        disp( "The configuration file is located : " + ...
            getenv("INI_FILE_NAME") );
        ext = filename( end-3 : end );
        disp("Filename : " + filename );
        if ext == ".mat"
            fprintf( 'Loading CurvStructs ... ' )
            data = load( filename, 'CurvStructs' );
            data = table2struct( data.CurvStructs );
            fprintf( 'Done\n' )
            using_mat = true;
            n = 1;
            status = ~isempty( data );
        else
            using_mat = false;
            [status, CurvStruct, err_msg] = ReadGCode_mex( 'ReadGCode', cmd, filename);
        end
    elseif cmd == ReadGCodeCmd.Read
        if using_mat
            if n < length( data )
                CurvStruct = data( n );
                n = n + 1;
                status = 1;
            else
                status = 0;
                CurvStruct = data( 1 );
            end
        else
            [ status, CurvStruct, err_msg ] = ReadGCode_mex( 'ReadGCode', cmd, filename );
        end
    end
else
    coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')

    my_path = StructTypeName.WDIR + "/src";
    coder.updateBuildInfo('addIncludePaths',my_path);

    pathRs274Src = StructTypeName.WDIR + "/../../rs274ngc/src";
    %     coder.updateBuildInfo('addDefines', '-DMEX_READGCODE')
    coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
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
    coder.updateBuildInfo('addLinkFlags', '-ldl');
    %    coder.updateBuildInfo('addIncludePaths', '$(START_DIR)/gen_mex/readgcode');
    coder.cinclude('cpp_interp.hpp');

    switch cmd
        case ReadGCodeCmd.Load
            status = coder.ceval( 'cpp_interp_init', [filename 0], coder.ref(err_msg) );
        case ReadGCodeCmd.Read
            is_loaded = false;
            is_loaded = coder.ceval( 'cpp_interp_loaded', coder.ref(err_msg) );
            if is_loaded
                status  = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct ), coder.ref(err_msg) );
            else
                status  = ReadGCodeError.InterpError;
            end
    end
end

if(0)
    fprintf(1, "[%d]%s\n", int32(status),"[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
    err_msg.msg);
end

ocn_assert( status < ReadGCodeError.InterpNotOpen, ...
    "[Line " + CurvStruct.Info.gcode_source_line + "] " + ...
    err_msg.msg, mfilename );

end
