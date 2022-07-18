function Y = c_opt_geom(X)
Y = X;
coder.ceval('c_opt_geom', coder.rref(X), coder.wref(Y));

end