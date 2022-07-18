function ctx = SplitLine(ctx, CrvStrct, L_split)
P0            = CrvStrct.P0;
P1            = CrvStrct.P1;
L             = MyNorm(P1 - P0); % length of original line segment
N             = floor(L/L_split);
L_split       = L/N;             % corrected L_split
alpha_old     = 0;
%
for k = 1:N
    CrvStrct.P0 = (1-alpha_old)*P0 + alpha_old*P1;
    %
    alpha               = k*L_split/L;
    CrvStrct.P1 = (1-alpha)*P0 + alpha*P1;
    alpha_old           = alpha;
    ctx.q_split.push(CrvStrct);
end

