function ctx = SplitSpline(ctx, Curv)


Spline=ctx.q_splines.get(Curv.sp_index);
sp = Spline.sp;

L_split=ctx.cfg.LSplit;

a=Curv.a_param;
b=Curv.b_param;
u0_tilda = a*0+b;
u1_tilda = a*1+b;

knots = sp.knots(4:end-3);

Idx1 = find(knots>u0_tilda, 1);
Idx2 = find(knots<u1_tilda, 1, 'last');

knots = [u0_tilda knots(Idx1(1):Idx2(1)) u1_tilda];

L=0;
k=1;

while k<length(knots)
    
    i=k;
    
    while L<L_split && k<length(knots)
        delta_L = SplineLengthApprox(ctx, Curv, knots(k), knots(k+1));
        L=L+delta_L;
        k=k+1;
    end

    Curv.a_param = knots(k)-knots(i);
    Curv.b_param = knots(i);

    ctx.q_split.push(Curv);

    L=0;
    
end


end
