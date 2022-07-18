function ctx = SplitHelix(ctx, CrvStrct, L_split)
%
theta   = CrvStrct.theta;
pitch   = CrvStrct.pitch;
%
L = LengthHelix(ctx, CrvStrct);
%
N             = ceil(L/L_split);
L_split       = L/N;             % corrected L_split
% CrvStrctSplit = repmat(CrvStrct, 1, N); % preallocation (MALLOC TO BE RECHECKED !)
%
u_old     = 0;
CrvStrctNew = CrvStrct;
%
for k = 1:N
    CrvStrctNew.theta = theta/N;
    CrvStrctNew.pitch = pitch;
    %
    P0prim = EvalHelix(CrvStrct, u_old);
    CrvStrctNew.P0 = P0prim;    
    %
    u     = k*L_split/L;
    P1prim = EvalHelix(CrvStrct, u);
    CrvStrctNew.P1 = P1prim;
    ctx.q_split.push(CrvStrctNew);
    %
    u_old = u;
end
