function c_prof_in(name) %#codegen
if coder.target('rtw')
%     coder.ceval('PROF_IN', coder.opaque('const char*', name));
end
end
