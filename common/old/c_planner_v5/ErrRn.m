function E = ErrRn(V1, V2)
% ErrRn

d = (V1-V2).^2;

E = sqrt(sum(d, 2));

end
