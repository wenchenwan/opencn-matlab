function [A, b] = BuildConstrJerk_v4(ctx, CurvStructs, Coeff, jmax,  ...
                                     BasisVal, BasisValD, BasisValDD, u_vec)
c_prof_block('BuildConstrJerk_v4');
                                 % import splines.*
%
Ncrv   = length(CurvStructs);
[M, N] = size(BasisVal);    
%
A      = sparse(6 * M * Ncrv,   N * Ncrv);  % preallocation
b      = zeros( 6 * M * Ncrv,   1);         % preallocation

% coder.varsize('A', [6*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz], [1,1]);
% coder.varsize('b', [6*FeedoptLimits.MaxNDiscr*FeedoptLimits.MaxNHorz, 1], [1,0]);

%
% q_opt  = Function(Bl, Coeff(:, 1));
% q_val  = q_opt.fast_eval(u_vec);
q_val = BasisVal*Coeff(:,1);

[~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStructs(1), u_vec);
%
R1 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(1, :)') + ...
      1.5*bsxfun(@times, BasisValD , r2D(1, :)') + ...
      0.5*bsxfun(@times, BasisValDD,r1D(1, :)')) , mysqrt(q_val));
  
R2 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(2, :)') + ...
  1.5*bsxfun(@times, BasisValD , r2D(2, :)') + ...
  0.5*bsxfun(@times, BasisValDD,r1D(2, :)')) , mysqrt(q_val));

R3 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(3, :)') + ...
  1.5*bsxfun(@times, BasisValD , r2D(3, :)') + ...
  0.5*bsxfun(@times, BasisValDD,r1D(3, :)')) , mysqrt(q_val));
% R2 = (BasisVal .* r3D(2, :)' + ...
%       1.5*BasisValD .* r2D(2, :)' + ...
%       0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
% R3 = (BasisVal .* r3D(3, :)' + ...
%       1.5*BasisValD .* r2D(3, :)' + ...
%       0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
%
A(1:6*M, 1:N)  = [R1;
                 -R1;
                  R2;
                 -R2;
                  R3;
                 -R3];
%
bC2 = jmax(1)*ones(M, 1);
bC3 = jmax(2)*ones(M, 1);
bC4 = jmax(3)*ones(M, 1);
%
b(1:6*M)       = [bC2;
                  bC2;
                  bC3;
                  bC3;
                  bC4;
                  bC4];
%
for k = 1:Ncrv-1
    [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStructs(k+1), u_vec);
    %
%     q_opt  = Function(Bl, Coeff(:, k+1));
%     q_val  = q_opt.fast_eval(u_vec);
    q_val = BasisVal*Coeff(:, k+1);
    %
    R1 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(1, :)') + ...
          1.5*bsxfun(@times, BasisValD , r2D(1, :)') + ...
          0.5*bsxfun(@times, BasisValDD,r1D(1, :)')) , mysqrt(q_val));
      
  R2 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(2, :)') + ...
      1.5*bsxfun(@times, BasisValD , r2D(2, :)') + ...
      0.5*bsxfun(@times, BasisValDD,r1D(2, :)')) , mysqrt(q_val));
  
  R3 = bsxfun(@times, (bsxfun(@times, BasisVal , r3D(3, :)') + ...
      1.5*bsxfun(@times, BasisValD , r2D(3, :)') + ...
      0.5*bsxfun(@times, BasisValDD,r1D(3, :)')) , mysqrt(q_val));
%     R2 = (BasisVal .* r3D(2, :)' + ...
%           1.5*BasisValD .* r2D(2, :)' + ...
%           0.5*BasisValDD.*r1D(2, :)') .* mysqrt(q_val);
%     R3 = (BasisVal .* r3D(3, :)' + ...
%           1.5*BasisValD .* r2D(3, :)' + ...
%           0.5*BasisValDD.*r1D(3, :)') .* mysqrt(q_val);
    %
    A(k*6*M+1:(k+1)*6*M, k*N+1:(k+1)*N) = ...
      [R1;
      -R1;
       R2;
      -R2;
       R3;
      -R3];
    %
    b(k*6*M+1:(k+1)*6*M) = [bC2;
                            bC2;
                            bC3;
                            bC3;
                            bC4;
                            bC4];
    %
end
       
