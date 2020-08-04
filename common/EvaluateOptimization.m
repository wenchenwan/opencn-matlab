function EvaluateOptimization(ctx)
mkdir('OptResults')
fprintf('Loading data ... ');
u_vec = ctx.u_vec;
OptStructs = ctx.q_opt.getall;
fprintf('OK\n');

N = length(OptStructs);
Nu = length(u_vec);

K = 0;

fprintf('Computing constraint maximization ... ');

mean_constraint = 0;

constraint_vec = zeros(1, Nu*N);

for k = 1:N
    
    OptStruct = OptStructs(k);
    [v_norm, acc, jerk] = CalcVAJ(ctx, OptStruct, ctx.Bl, u_vec);
    v_norm = v_norm/OptStruct.FeedRate;
    acc = abs(acc)./ctx.cfg.amax.';
    jerk = abs(jerk)./ctx.cfg.jmax.';
    
%     plot(u_vec + k - 1, v_norm, u_vec + k - 1, acc, u_vec + k - 1, jerk)
%     hold on;
    
    constraint = max(max(max(acc, jerk), v_norm), [], 1);
    constraint_vec(1+K*Nu:(K+1)*Nu) = constraint;
    mean_constraint = mean_constraint + sum(constraint)/Nu;
    
    K = K + 1;
    
end
figure('units','normalized','outerposition',[0 0 1 1])
subplot(1,2,1)
plot(constraint_vec)
subplot(1,2,2)
histogram(constraint_vec)

if K >= 1
    mean_constraint = mean_constraint/K;
end

fprintf('OK\n');

fprintf('Constraint Maximization: %5.2f%%\n', mean_constraint*100);
tt = sprintf('File: %s\nConstraint: %4.2f%%, NHorz = %d, CutOff = %.2fmm, LSplit = %.2fmm\nNBreak = %d, NDiscr = %d',...
    ctx.cfg.source, mean_constraint*100, ctx.cfg.NHorz, ctx.cfg.CutOff, ctx.cfg.LSplit, ctx.cfg.NBreak, ctx.cfg.NDiscr);

fname = split(ctx.cfg.source, '/');
filename_png = sprintf('%s_NHorz_%d_CutOff_%.2fmm_LSplit_%.2fmm_NBreak_%d_NDiscr_%d.png',...
    fname{end}, ctx.cfg.NHorz, ctx.cfg.CutOff, ctx.cfg.LSplit, ctx.cfg.NBreak, ctx.cfg.NDiscr);
filename_fig = sprintf('%s_NHorz_%d_CutOff_%.2fmm_LSplit_%.2fmm_NBreak_%d_NDiscr_%d.fig',...
    fname{end}, ctx.cfg.NHorz, ctx.cfg.CutOff, ctx.cfg.LSplit, ctx.cfg.NBreak, ctx.cfg.NDiscr);
sgtitle(tt, 'interpreter', 'none')
saveas(gcf, fullfile('OptResults', filename_png));
saveas(gcf, fullfile('OptResults', filename_fig));

end