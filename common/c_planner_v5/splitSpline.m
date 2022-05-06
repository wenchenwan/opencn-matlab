function ctx = splitSpline(ctx, Curv)
% SplitSpline
%
% Split the B spline into shorter.
% It is needed for Feedrate Planning to have curv with almost same length

Spline=ctx.q_spline.get(Curv.sp_index);
sp = Spline.sp;

% Max length of the segment
L_split=ctx.cfg.LSplit;

% Parameter of paramtretric abcissa
a=Curv.a_param;
b=Curv.b_param;
% First and last point of the B spline
u0_tilda = a*0+b;
u1_tilda = a*1+b;

ustart_tilda = u0_tilda;
uend_tilda = u0_tilda;

% While 
while(uend_tilda < u1_tilda && uend_tilda ~= -1)
    % Find the point uend_tilda at a length L_split form ustart_tilda
    uend_tilda  = SplineLengthFindU_up(ctx, Curv, L_split, ustart_tilda);
    
    % Assigne a and b of the next curv
    if uend_tilda ~= -1 % if spline is not too short
        Curv.a_param = uend_tilda - ustart_tilda;
        Curv.b_param = ustart_tilda;
    else
        Curv.a_param = u1_tilda - ustart_tilda;
        Curv.b_param = ustart_tilda;
    end
    % Push the next curv
    ctx.q_split.push(Curv);

    ustart_tilda = uend_tilda;
end

end
