function [v_norm, a, j] = CalcVAJ_v5(ctx, CurvStructs, Bl, Coeff, u_cell)
%
% import splines.*
%
% Ntot = 0;
% for k = 1:Ncrv
%     Ntot = Ntot + size(u_cell{k}, 2);
% end

v_norm    = zeros(1, 1);
a         = zeros(3, 1);
j         = zeros(3, 1);

% v_norm = [];
% a = [];
% j = [];

index = 1;

%
for k = 1:1
%     qSpl = Function(Bl, Coeff(:, k));
    u_vec = u_cell{k};
    %
    [~, r1D, r2D, r3D] = EvalCurvStruct(ctx, CurvStructs(k), u_vec);
    r1D_norm             = mysqrt(sum(r1D.^2));  % norm
    %
%     q_val   = qSpl.fast_eval(u_vec);
%     qD_val  = qSpl.derivative.fast_eval(u_vec);
%     qDD_val = qSpl.derivative(2).fast_eval(u_vec);
    
    q_val = zeros(size(u_vec));
    qD_val = zeros(size(u_vec));
    qDD_val = zeros(size(u_vec));

    % TODO: Optimize this with a single call to eval, and maybe a basis
    % precompute?
    for iu = 1:numel(u_vec)
        if CurvStructs.Info.zspdmode==ZSpdMode.ZN
            t = (6*u_vec(iu)/CurvStructs.ConstJerk)^(1/3);
            q_val(iu) = (CurvStructs.ConstJerk*t^2/2)^2;
            qD_val(iu) = 2*CurvStructs.ConstJerk*t; 
            qDD_val(iu) = 4/t^2;
        elseif CurvStructs.Info.zspdmode==ZSpdMode.NZ
            t = (6*(1-u_vec(iu))/CurvStructs.ConstJerk)^(1/3);
            q_val(iu) = (CurvStructs.ConstJerk*t^2/2)^2;
            qD_val(iu) = -2*CurvStructs.ConstJerk*t;
            qDD_val(iu) = 4/t^2;
        elseif CurvStructs.Info.zspdmode==ZSpdMode.ZZ
            error('Should not get here');
        else %% ZSpdMode.NN
            [v1, v2, v3] = bspline_eval(Bl, Coeff(:, k)', u_vec(iu));
            q_val(iu) = v1;
            qD_val(iu) = v2;
            qDD_val(iu) = v3;
        end
        
    end
    
    
    q_val = q_val';
    qD_val = qD_val';
    qDD_val = qDD_val';
    
    tmp1 = bsxfun(@times, r1D_norm, mysqrt(q_val'));
    tmp2 = bsxfun(@times, r2D, q_val') + 0.5*bsxfun(@times, r1D, qD_val');
    tmp3 = bsxfun(@times, r3D, (q_val.^(3/2))') + ...
            1.5*bsxfun(@times, r2D, bsxfun(@times, qD_val',mysqrt(q_val)')) + ...
            0.5*bsxfun(@times, r1D, bsxfun(@times, qDD_val',mysqrt(q_val)')); 
  
    v_norm = tmp1;
    a = tmp2;%zeros(3, size(tmp2, 2));
    j = tmp3;
end





