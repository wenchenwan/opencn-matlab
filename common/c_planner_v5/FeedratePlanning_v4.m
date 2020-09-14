function [ctx, Coeff, NCoeff, success, status] = FeedratePlanning_v4(ctx, CurvStructs0, amax, jmax, ...
                                     BasisVal, BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, N_Hor)

                                 
%
c_prof_in(mfilename);
CurvStructs = CurvStructs0(1:N_Hor);
coder.varsize('CurvStructs', [1, Inf], [0,1]);
Ncrv   = length(CurvStructs);
[~, N] = size(BasisVal);

if ctx.cfg.DebugFeedratePlanning

fprintf('===============================\n')
fprintf('====== FEEDRATE PLANNING ======\n')
fprintf('===============================\n')

fprintf('v_0  = %f\n', ctx.v_0)
fprintf('at_0 = %f\n', ctx.at_0)

fprintf('v_1  = %f\n', ctx.v_1)
fprintf('at_1 = %f\n', ctx.at_1)

for k = 1:Ncrv
    PrintCurvStruct(ctx, CurvStructs(k));
end

fprintf('===============================\n')
fprintf('===============================\n')

end


%
%% FIRST setup of Linear Program (LP) WITHOUT jerk constraint
f       = -repmat(BasisIntegr, 1, Ncrv);  % maximize integral of q
%% equality constraints
success = false;
max_increase = 5;

% to satisfy the coder
if coder.target('rtw') || coder.target('mex')
    coder_A = 0;
    coder.varsize('coder_A', [Inf Inf], [1, 1]);
    A = sparse(coder_A);
    Aeq = coder_A;
    
    coder_b = 0;
    coder.varsize('coder_b', [1, Inf], [0, 1]);
    b = coder_b;
    beq = coder_b;
    Coeff0 = zeros(N, Ncrv); 
end
% -----------


[A, b, Aeq, beq] = BuildConstr_v4(ctx, CurvStructs, amax, ctx.v_0, ctx.at_0, ctx.v_1, ctx.at_1, ...
                                  BasisVal, BasisValD, u_vec);

coder.varsize('f', [Inf, Inf], [1, 1]);
[Coeff0, success, status] = c_simplex(f, A, b, Aeq, beq);


%
% tic
% Coeff1 = linprog(f, A, b, Aeq, beq, [], [], options);
% toc Coeff(:, end-N_Hor+2:end) = C(:, 2:end);
%
if ~success
    Coeff = [];
    NCoeff = int32(0);
    return;
end
Coeff1  = reshape(Coeff0, N, Ncrv);
DebugLog('Coeff1 = ')
for k = 1:N
    DebugLog('%.4f ', Coeff1(k, 1));
end
DebugLog('\n')

%% SECOND setup of Linear Program (LP) WITH jerk constraint
success = false;
max_increase = 20;

Coeff2 = zeros(N, Ncrv); % satisfy the coder
while ~success && max_increase > 0
    [A_jerk, b_jerk] = BuildConstrJerk_v4(ctx, CurvStructs, Coeff1, jmax,  ...
                                          BasisVal, BasisValD, BasisValDD, u_vec);

    %
    Atot = [A;
            A_jerk];
    %    
    btot = [b;
            b_jerk];


    [Coeff2, success, status] = c_simplex(f, Atot, btot, Aeq, beq);
    if ~success
%         amax = amax*1.1;
        ctx.jmax_increase_count = ctx.jmax_increase_count + 1;
        jmax = jmax*2; % TODO: valeur à ajuster, avant: 1.1...
        fprintf('WARNING: (Jerk) Increasing jmax to [%f,%f,%f]\n', jmax(1), jmax(2), jmax(3));
        max_increase = max_increase - 1;
    end
    
end

if ~success
    Coeff = [];
    NCoeff = int32(0);
    return;
end
%
% tic
% Coeff1 = linprog(f, Atot, btot, Aeq, beq, [], [], options);
% toc
%
Coeff3 = reshape(Coeff2, N, Ncrv);
DebugLog('Coeff3 = ')
for k = 1:N
    DebugLog('%.4f ', Coeff3(k, 1));
end
DebugLog('\n')
% 
[v_0, a_0]  = CalcVAJ_v5(ctx, CurvStructs(1), Bl, Coeff3(:, 1), {1});
[~, r1D]         = EvalCurvStruct(ctx, CurvStructs(1), 1);
t_end            = r1D/MyNorm(r1D); % unit tangential vector
at_0 = a_0'*t_end; % tangential acceleration at the end of first piece in horizon
ctx.v_0 = v_0;
ctx.at_0 = at_0;
% Coeff = Coeff3(:, 1);
% Coeff = zeros(FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz);
% coder.varsize('Coeff', [Inf, Inf], [1,1]);
Coeff = Coeff3;
NCoeff = int32(N);
c_prof_out(mfilename);
