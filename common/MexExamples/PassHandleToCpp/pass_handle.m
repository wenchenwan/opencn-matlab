function pass_handle(ptr)
    coder.updateBuildInfo('addSourceFiles', 'use_handle.cpp');
    coder.cinclude('use_handle.h');
    coder.ceval('use_handle', ptr);
end