function ctx = SplitLineHelix(ctx, Curv)

a=Curv.a_param;
b=Curv.b_param;

L=LengthCurv(ctx, Curv, 0, 1);
L_split=ctx.cfg.LSplit;

if L<2*L_split
    ctx.q_split.push(Curv);
    return;
end

N = ceil(L/L_split);

L_split = L/N;

for k = 1:N
    
    u_0 = (k-1)*(L_split/L);
    u_1 = k*(L_split/L);
    
    u_tilda_0 = a*u_0+b;
    u_tilda_1 = a*u_1+b;
    
    Curv.a_param = u_tilda_1 - u_tilda_0;
    Curv.b_param = u_tilda_0;
    
    ctx.q_split.push(Curv);
    
end


end


