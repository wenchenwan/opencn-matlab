function value = main_call
    value = int32(0);
    coder.updateBuildInfo('addSourceFiles','lib.cpp');
    coder.cinclude('lib.h');
    value = coder.ceval('lib_function1');
    
end