function ctx = SplitSpline(ctx, Curv)


Spline=ctx.q_splines.get(Curv.sp_index);
sp = Spline.sp;

L_split=ctx.cfg.LSplit;

a=Curv.a_param;
b=Curv.b_param;
u0_tilda = a*0+b;
u1_tilda = a*1+b;

ux_tilda  = SplineLengthFindU_up(ctx, Curv, L_split, u0_tilda);

if ux_tilda ~= -1 % if spline is not too short
    Curv.a_param = ux_tilda - u0_tilda;   
end
ctx.q_split.push(Curv);

end
