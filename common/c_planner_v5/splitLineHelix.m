function ctx = splitLineHelix(ctx, initCurv)
% splitLine
%
% 

% Initialization of the splittedCurv
splittedCurv = initCurv;
% Initialization of the ZeroStart and ZeroEnd cutted Curv for the coder
CurvStruct1  = initCurv;
CurvStruct2  = initCurv;
CurvStruct3  = initCurv;

% Parameter of paramtretric abcissa
a = initCurv.a_param;
b = initCurv.b_param;

L = LengthCurv(ctx, initCurv, 0, 1);
L_split = ctx.cfg.LSplit;

if L < 2*L_split
    % Cut ZeroStrt and ZeroEnd needed for optimization
    if initCurv.Info.zspdmode == ZSpdMode.ZN
        [ CurvStruct1, CurvStruct2 ] = cutZeroStart( ctx, initCurv );
        CurvStruct2.a_param = initCurv.a_param;
        ctx.q_split.push(CurvStruct1);
        ctx.q_split.push(CurvStruct2);
    elseif initCurv.Info.zspdmode == ZSpdMode.NZ
        [ CurvStruct1, CurvStruct2 ] = cutZeroEnd( ctx, initCurv );
        CurvStruct1.a_param = initCurv.a_param;
        CurvStruct1.b_param = initCurv.b_param;
        ctx.q_split.push(CurvStruct1);
        ctx.q_split.push(CurvStruct2);
    elseif initCurv.Info.zspdmode == ZSpdMode.ZZ
        [ CurvStruct1, CurvStruct2 ] = cutZeroStart( ctx, initCurv );
        [ CurvStruct2, CurvStruct3 ] = cutZeroEnd( ctx, CurvStruct2 );
        CurvStruct2.a_param = initCurv.a_param;
        CurvStruct2.b_param = initCurv.b_param;
        ctx.q_split.push(CurvStruct1);
        ctx.q_split.push(CurvStruct2);
        ctx.q_split.push(CurvStruct3);
    else
        ctx.q_split.push(initCurv);
    end
    
    return;
end

% Number of sub segments
N = ceil(L/L_split);

% Length of the sub segments
L_split = L/N;

% Loop
for k = 1:N
    
    u_0 = (k-1)*(L_split/L);
    u_1 = k*(L_split/L);
    
    u_tilda_0 = a*u_0+b;
    u_tilda_1 = a*u_1+b;
    
    splittedCurv.a_param = u_tilda_1 - u_tilda_0;
    splittedCurv.b_param = u_tilda_0;

    % Assigns correctly the zspdmode for each splitted curvStruct
    splittedCurv = splitZspdmode( initCurv, splittedCurv, k, k, 1, N );
    
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
    
end

end


