function [ status, CurvStruct ] = ReadGCode( cmd, filename )
%#codegen
% coder.extrinsic('ReadGCode_mex');
% Wrapper for pulling the next gcode line from the interpreter
persistent n data using_mat

if coder.target('mex') 
    CurvStruct = constrCurvStructType;

    coder.updateBuildInfo('addDefines', '_POSIX_C_SOURCE=199309L')
    pathRs274Src = '$(START_DIR)/../../rs274ngc/src';
    % coder.updateBuildInfo('addDefines', 'DEBUG_RS274')
%     coder.updateBuildInfo('addDefines', '#define MEX_READGCODE')
    coder.updateBuildInfo('addCompileFlags', '-fdiagnostics-color=always')
    coder.updateBuildInfo('addSourceFiles','cpp_interp.cpp', '$(START_DIR)/../common/src');
    coder.updateBuildInfo('addSourceFiles','directives.cc', pathRs274Src);
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
    
    status = int32(0);
    switch cmd
        case ReadGCodeCmd.Load
            status = coder.ceval( 'cpp_interp_init', [filename 0] );
        case ReadGCodeCmd.Read
            is_loaded = int32(0);
            is_loaded = coder.ceval( 'cpp_interp_loaded' );
            if is_loaded
                status = coder.ceval( 'cpp_interp_read', coder.ref( CurvStruct ) );
            else
                status = int32(0);
            end
    end
elseif coder.target('matlab') 
    if cmd == ReadGCodeCmd.Load
        setenv( "INI_FILE_NAME", pwd + "/config.ini" );
        disp( "The configuration file is located : " + ...
              getenv("INI_FILE_NAME") );
        ext = filename( end-3 : end );
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
            [status, CurvStruct] = ReadGCode_mex( 'ReadGCode', cmd, filename );

            CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
            CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
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
            [ status, CurvStruct ] = ReadGCode_mex( 'ReadGCode', cmd, filename );

            CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
            CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );
        end
    end
elseif coder.target('rtw')

    if cmd == ReadGCodeCmd.Load

        CurvStruct = constrCurvStructType;
        status = int32( 0 );
        status = coder.ceval( 'c_open_gcode', [filename, 0], coder.ref( CurvStruct ) );
    elseif cmd == ReadGCodeCmd.Read

        CurvStruct = constrCurvStructType;
        status = int32( 0 );
        status = coder.ceval( 'c_read_and_exec_gcode', '', coder.ref( CurvStruct ) );

        CurvStruct.R0( 4 : end ) = deg2rad( CurvStruct.R0( 4 : end ) );
        CurvStruct.R1( 4 : end ) = deg2rad( CurvStruct.R1( 4 : end ) );

    end
else
    error('Unknown target');
end

end
