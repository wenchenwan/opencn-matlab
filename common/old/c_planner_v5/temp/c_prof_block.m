function c_prof_block(name) %#codegen
if coder.target('rtw')
%     coder.ceval('PROF_BLOCK', coder.opaque('const char*', name));
end
end
