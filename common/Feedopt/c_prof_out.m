function c_prof_out(name) %#codegen
if coder.target('rtw')
%     coder.ceval('PROF_OUT', coder.opaque('const char*', name));
end
end
