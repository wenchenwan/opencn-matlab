function [u, N] = Calc_u_v4(Bl, Coeff, dt)
%
% import splines.*
%
[~, Ncrv] = size(Coeff);
u = zeros(1, 10000);
%
uk   = 0;
% u    = uk;
k    = 1;
N    = int32(1);  % number of samples
%
% qSpl  = Function(Bl, Coeff(:, 1));
% qSplD = qSpl.derivative;
%
%
while N <= 10000
%     qk   = qSpl.fast_eval(uk);
%     dk   = qSplD.fast_eval(uk);
    [qk, dk, ~] = bspline_eval(Bl, Coeff(:,k), uk);
    ukp1 = uk + dk*dt^2/4 + mysqrt(qk)*dt;
    %
    if ukp1 <= 1 - 1e-3
        u(N) = ukp1;
        uk   = ukp1;
        N    = N + 1;
%     else
% %         u_cell(k) = u;   % store previous calculated values
%         ukp1      = 1;
% %         qkp1      = qSpl.fast_eval(ukp1);
%         [qkp1,~] = c_bspline_eval(Bl, Coeff(:,k), ukp1);
%         Trest     = 2*(ukp1 - uk) / (mysqrt(qkp1) + mysqrt(qk));
%         k         = k + 1;
%         %
%         if k > Ncrv
%             break;
%         end
% %         qSpl      = Function(Bl, Coeff(:, k));
% %         qSplD     = qSpl.derivative;
%         dt_begin  = dt - Trest;
%         uk        = 0;
%         %
% %         qk        = qSpl.fast_eval(uk);
% %         dk        = qSplD.fast_eval(uk);
%         [qk, dk] = c_bspline_eval(Bl, Coeff(:,k), uk);
%         ukp1      = uk + dk*dt_begin^2/4 + mysqrt(qk)*dt_begin; 
%         u         = ukp1;
%         N         = N + 1;
    else
        break;
    end
end
%
% t = 0:dt:(N-1)*dt;
