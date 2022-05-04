function [A, b, Aeq, beq ] = BuildConstr_v4(ctx, CurvStructs, amax, v_0, at_0, v_1, at_1, ...
    BasisVal, BasisValD, u_vec)

DebugLog(DebugCfg.Global, 'BuildConstr_v4 with Ncrv = %d, amax = [%f, %f, %f], v_0 = %f, at_0 = %f, v_1 = %f, at_1 = %f\n', ...
    int32(numel(CurvStructs)), amax(1), amax(2), amax(3), v_0, at_0, v_1, at_1);

Bl = ctx.Bl;
if ctx.cfg.UseDynamicBreakpoints
    NBreak = max(floor(LengthCurv(ctx, CurvStructs(1), 0, 1)/ctx.cfg.DynamicBreakpointsDistance), 4);
    if ctx.cfg.UseLinearBreakpoints
        Bl = bspline_create(ctx.cfg.SplineDegree, linspace(0,1,NBreak));
    end
    
    [BasisVal, BasisValD] = bspline_base_eval(Bl, u_vec);
end


c_prof_in(mfilename);
Ncrv   = length(CurvStructs);
%Bl
[M, N] = size(BasisVal);               
Nx  = N * Ncrv;
Nc  = 7 * M * Ncrv;
Nec = 2 * (Ncrv + 1);
% M     : number of discretization
% N     : number of coefficients
% Nx    : number of decision variable
% Nc    : number of inequality constraints
% Nec   : number of equality constraints

A      = sparse(Nc,   Nx); % preallocation
b      = zeros(Nc,   1);   % preallocation
Aeq    = zeros(Nec, Nx);   % preallocation
beq    = zeros(Nec, 1);    % preallocation
% A     : Inequality matrix
% b     : Inequality vector
% Aeq   : Inequality matrix
% beq   : Inequality vector

% coder.varsize('b', [7*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);
% coder.varsize('Aeq', [2*(FeedoptLimits.MaxNHorz+1), FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]);
% coder.varsize('beq', [2*(FeedoptLimits.MaxNHorz+1), 1], [1,0]);

% Compute the partial derivatives 
[~, r1D, r2D] = EvalCurvStruct(ctx, CurvStructs(1), u_vec);

vmax = CurvStructs(1).Info.FeedRate;

r1D_sqnorm    = sum(r1D.^2);      % squared norm
%
t_0 = r1D(:, 1)/norm(r1D(:, 1));  % unit tangent vector @ start
%
%
R1 = bsxfun(@times, r2D(1, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(1, :)' , BasisValD);
R2 = bsxfun(@times, r2D(2, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(2, :)' , BasisValD);
R3 = bsxfun(@times, r2D(3, :)' , BasisVal) + 0.5*bsxfun(@times, r1D(3, :)' , BasisValD);

%
A(1:7*M, 1:N)  = [BasisVal;
    R1;
    -R1;
    R2;
    -R2;
    R3;
    -R3];
%
bC1 = (vmax)^2./r1D_sqnorm';
bC2 = amax(1)*ones(M, 1);
bC3 = amax(2)*ones(M, 1);
bC4 = amax(3)*ones(M, 1);
%
b(1:7*M)       = [bC1;
    bC2;
    bC2;
    bC3;
    bC3;
    bC4;
    bC4];
%
Aeq(1:2, 1:N)   = [BasisVal(1, :);
    t_0' * [r2D(1, 1)   * BasisVal(1, :)   + 0.5*r1D(1, 1)   * BasisValD(1, :);
    r2D(2, 1)   * BasisVal(1, :)   + 0.5*r1D(2, 1)   * BasisValD(1, :);
    r2D(3, 1)   * BasisVal(1, :)   + 0.5*r1D(3, 1)   * BasisValD(1, :)]];
beq(1:2)       = [(v_0(1)^2)/r1D_sqnorm(1);
    at_0(1)];

% This should be the correct behavior for a single segment,
% reusing the r1D norm
r1Dn_sqnorm = r1D_sqnorm;

for k = 1:Ncrv-1
    if ctx.cfg.UseDynamicBreakpoints
        NBreak = max(4, floor(LengthCurv(ctx, CurvStructs(k+1), 0, 1)/ctx.cfg.DynamicBreakpointsDistance));
        if ctx.cfg.UseLinearBreakpoints
            Bl = bspline_create(ctx.cfg.SplineDegree, linspace(0,1,NBreak));
        end
        
        [BasisVal, BasisValD] = bspline_base_eval(Bl, u_vec);
    end
    [M, N] = size(BasisVal);
    
    [~, r1Dn, r2Dn] = EvalCurvStruct(ctx, CurvStructs(k+1), u_vec);
    vmax            = CurvStructs(k+1).FeedRate;
    r1Dn_sqnorm     = sum(r1Dn.^2);        % squared norm
    bC1 = (vmax)^2./r1Dn_sqnorm';
    t_1 = r1D(:, end)/norm(r1D(:, end));   % unit tangent vector @ end of previous piece
    %
    R1 = bsxfun(@times, r2Dn(1, :)' , BasisVal) + 0.5*bsxfun(@times, r1Dn(1, :)' , BasisValD);
    R2 = bsxfun(@times, r2Dn(2, :)' , BasisVal) + 0.5*bsxfun(@times, r1Dn(2, :)' , BasisValD);
    R3 = bsxfun(@times, r2Dn(3, :)' , BasisVal) + 0.5*bsxfun(@times, r1Dn(3, :)' , BasisValD);
    %
    A(k*7*M+1:(k+1)*7*M, k*N+1:(k+1)*N) = ...
        [BasisVal;
        R1;
        -R1;
        R2;
        -R2;
        R3;
        -R3];
    %
    b(k*7*M+1:(k+1)*7*M) = [bC1;
        bC2;
        bC2;
        bC3;
        bC3;
        bC4;
        bC4];
    %
    Aeq(2*k+1, (k-1)*N+1:k*N) =  (t_1'*r1D(:, end))^2 * BasisVal(end, :);
    Aeq(2*k+1, k*N+1:(k+1)*N) = -(t_1'*r1Dn(:, 1))^2  * BasisVal(1,   :);
    
    Aeq(2*k+2, (k-1)*N+1:k*N) =   t_1'*[...
        r2D(1, end)   * BasisVal(end, :)   + 0.5*r1D(1, end)   * BasisValD(end, :);
        r2D(2, end)   * BasisVal(end, :)   + 0.5*r1D(2, end)   * BasisValD(end, :);
        r2D(3, end)   * BasisVal(end, :)   + 0.5*r1D(3, end)   * BasisValD(end, :)];
    %
    Aeq(2*k+2, k*N+1:(k+1)*N) = -(t_1'*[...
        r2Dn(1, 1)   * BasisVal(1, :)   + 0.5*r1Dn(1, 1)   * BasisValD(1, :);
        r2Dn(2, 1)   * BasisVal(1, :)   + 0.5*r1Dn(2, 1)   * BasisValD(1, :);
        r2Dn(3, 1)   * BasisVal(1, :)   + 0.5*r1Dn(3, 1)   * BasisValD(1, :)]);
    %
    r1D = r1Dn;
    r2D = r2Dn;
end
%
t_1 = r1D(:, end)/norm(r1D(:, end));   % unit tangent vector @ end of previous piece
%
Aeq(end-1:end, end-N+1:end)   = [BasisVal(end, :);
    t_1' * [...
    r2D(1, end) * BasisVal(end, :) + 0.5*r1D(1, end) * BasisValD(end, :);
    r2D(2, end) * BasisVal(end, :) + 0.5*r1D(2, end) * BasisValD(end, :);
    r2D(3, end) * BasisVal(end, :) + 0.5*r1D(3, end) * BasisValD(end, :)]];
%
beq(end-1:end) = [(v_1^2)/r1Dn_sqnorm(end);
    at_1];

c_prof_out(mfilename);


% Add a ramp on the acceleration and speed limits
vel_ramp = linspace(1, ctx.cfg.opt.VEL_RAMP_OVER_WINDOWS, M)';
acc_ramp = repmat(linspace(1, ctx.cfg.opt.ACC_RAMP_OVER_WINDOWS, M)',1,6);

if( Ncrv > 1 )
    ramp = [ones(M, 7), vel_ramp, acc_ramp, ...
            repmat([vel_ramp(end), acc_ramp(end,:)], M, Ncrv-2)];
    b  = b .* ramp(:);
end

% if( isempty( ctx.at_1 ) )
%     Aeq = Aeq(1 : end -1, : );
%     beq = beq( 1 : end -1 );
% end
end

