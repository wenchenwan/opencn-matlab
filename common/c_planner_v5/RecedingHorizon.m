function Coeff = RecedingHorizon(ctx, CurvStructs, amax, jmax, v_0, at_0, v_1, at_1, ...
                                 BasisVal, BasisValD, BasisValDD, BasisIntegr, Bl, u_vec, N_Hor)

coder.cstructname(CurvStructs, 'CurvStruct');                             
%

Ncrv   = length(CurvStructs);
Coeff  = zeros(Bl.n, Ncrv); % preallocation

% coder.varsize('Coeff', [1000, 50], [1, 1]); 
C = zeros(Bl.n, N_Hor);
%
if Ncrv <= N_Hor
    Coeff = FeedratePlanning_v4(ctx, CurvStructs, amax, jmax, v_0, at_0, v_1, at_1, ...
                                BasisVal, BasisValD, BasisValDD, BasisIntegr, Bl, u_vec);
else
    at_0 = 0;
    v_0  = 0.1; % 0.1;   % change to 0 later  !!!!!
    for k = 1:Ncrv-N_Hor+1
        C = FeedratePlanning_v4(ctx, CurvStructs(k:k+N_Hor-1), amax, jmax, v_0, at_0, v_1, at_1, ...
            BasisVal, BasisValD, BasisValDD, BasisIntegr, Bl, u_vec);
        Coeff(:, k) = C(:, 1); % keep solution of the first piece in horizon
        [v_0, a_0]  = CalcVAJ_v5(CurvStructs(k), Bl, C(:, 1), {1});
        [~, r1D]         = EvalCurvStruct(ctx, CurvStructs(k), 1);
        t_end            = r1D/MyNorm(r1D); % unit tangential vector
        at_0 = a_0'*t_end; % tangential acceleration at the end of first piece in horizon
    end
    Coeff(:, end-N_Hor+2:end) = C(:, 2:end);
end

%
