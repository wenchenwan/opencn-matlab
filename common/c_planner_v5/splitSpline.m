function ctx = splitSpline(ctx, initCurv)
% SplitSpline
%
% Split the B spline into shorter.
% It is needed for Feedrate Planning to have curv with almost same length

% Initialization of the splittedCurv
splittedCurv = initCurv;
% Initialization of the ZeroStart and ZeroEnd cutted Curv for the coder
CurvStruct1  = initCurv;
CurvStruct2  = initCurv;
CurvStruct3  = initCurv;

% Max length of the segment
L_split = ctx.cfg.LSplit;

% Parameter of paramtretric abcissa
a = initCurv.a_param;
b = initCurv.b_param;
% First and last point of the B spline
u0_tilda = a*0+b;
u1_tilda = a*1+b;
% Initialization of the boudaries of the splittedCurv
ustart_tilda = u0_tilda;
uend_tilda = u0_tilda;

% Loop 
while(uend_tilda < u1_tilda && uend_tilda ~= -1)
    % Find the point uend_tilda at a length L_split form ustart_tilda
    uend_tilda  = SplineLengthFindU_up(ctx, initCurv, L_split, ustart_tilda);
    
    % Assigne a and b of the next curv
    if uend_tilda ~= -1 % if spline is not too short
        splittedCurv.a_param = uend_tilda - ustart_tilda;
        splittedCurv.b_param = ustart_tilda;
    else
        splittedCurv.a_param = u1_tilda - ustart_tilda;
        splittedCurv.b_param = ustart_tilda;
    end

    % Assigns correctly the zspdmode for each splitted curvStruct
    splittedCurv = splitZspdmode( initCurv, splittedCurv, ustart_tilda, uend_tilda, u0_tilda, -1);
    
    % Cut ZeroStrt and ZeroEnd needed for optimization
    if splittedCurv.Info.zspdmode == ZSpdMode.ZN
        [ CurvStruct1, CurvStruct2 ] = cutZeroStart( ctx, splittedCurv );
        CurvStruct2.a_param = splittedCurv.a_param;
        ctx.q_split.push(CurvStruct1);
        ctx.q_split.push(CurvStruct2);
    elseif splittedCurv.Info.zspdmode == ZSpdMode.NZ
        [ CurvStruct1, CurvStruct2 ] = cutZeroEnd( ctx, splittedCurv );
        CurvStruct1.a_param = splittedCurv.a_param;
        CurvStruct1.b_param = splittedCurv.b_param;
        ctx.q_split.push(CurvStruct1);
        ctx.q_split.push(CurvStruct2);
    elseif splittedCurv.Info.zspdmode == ZSpdMode.ZZ
        [ CurvStruct1, CurvStruct2 ] = cutZeroStart( ctx, splittedCurv );
        [ CurvStruct2, CurvStruct3 ] = cutZeroEnd( ctx, CurvStruct2 );
        CurvStruct2.a_param = splittedCurv.a_param;
        CurvStruct2.b_param = splittedCurv.b_param;
        ctx.q_split.push(CurvStruct1);
        ctx.q_split.push(CurvStruct2);
        ctx.q_split.push(CurvStruct3);
    else
        ctx.q_split.push(splittedCurv);
    end

    ustart_tilda = uend_tilda;
end

end
