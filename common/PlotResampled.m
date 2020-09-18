function PlotResampled(ctx, dt)

% fprintf('Skipped %d segments\n', ctx.Skipped);

% Cur
% 
% if ~exist('CurvOpt', 'var')
%     error('NO OPTIMIZED CURVES')
% end

close all

uvec = zeros(200000, 1);
pvec = zeros(200000, 3);
kvec = zeros(200000, 1);

vvec = zeros(200000, 1);
avec = zeros(200000, 3);
jvec = zeros(200000, 3);

fvec = zeros(200000, 1);
cfvec = zeros(200000, 1);

ktick = 1;

state = ResampleState(dt);
N = ctx.q_opt.size();
fprintf('Resampling ...\n');
for k = 1:N
    if IsEnabledDebugLog(DebugCfg.OptimProgress)
        fprintf('%4d/%d\n', k, N);
    end
    Curv = ctx.q_opt.get(k);
    SplineCurv = ctx.q_splines.get(Curv.sp_index);
    Curv.MaxConstantFeedRate = GetCurvMaxFeedrate(ctx, Curv);
    
    state = ResampleNoCtx(state, ctx.Bl, Curv);
    while ~state.go_next
        state.dt = dt;    
        r0D = EvalPosition(Curv, SplineCurv, state.u);
        [Vnorm, Acc, Jerk] = CalcVAJ(ctx, Curv, ctx.Bl, state.u);
        pvec(ktick, :) = r0D;
        uvec(ktick) = state.u + double(k) - 1;
        kvec(ktick) = k;
        vvec(ktick) = Vnorm;
        avec(ktick, :) = Acc;
        jvec(ktick, :) = Jerk;
        fvec(ktick, :) = Curv.FeedRate*60;
        cfvec(ktick, :) = Curv.MaxConstantFeedRate*60;
        gvec(ktick, :) = Curv.gcode_source_line;
        ktick = ktick + 1;
        state = ResampleNoCtx(state, ctx.Bl, ctx.q_opt.get(k));
    end
    
    state.go_next = false;
    if ktick > 200000
        warning('Breaking because ktick > 200000')
        break;
    end
end

ktick = ktick - 1;

uvec = uvec(1:ktick);
vvec = vvec(1:ktick, :);
jvec = jvec(1:ktick, :);
avec = avec(1:ktick, :);
pvec = pvec(1:ktick, :);
fvec = fvec(1:ktick);
kvec = kvec(1:ktick);
cfvec = cfvec(1:ktick);

avec = avec./ctx.cfg.amax;
jvec = jvec./ctx.cfg.jmax;

data = table(uvec, kvec, pvec, vvec, avec, jvec, fvec, cfvec);

% while ~ctx.resample_end
% %     fprintf('ctx.resample_k = %d\n', ctx.resample_k);
%     r0D = EvalCurvStruct(ctx, ctx.q_opt.get(ctx.resample_k), ctx.resample_u);
%     pvec(ktick, :) = r0D;
%     uvec(ktick) = ctx.resample_u;
%     
%     [ctx, again, again_t] = ResampleTick(ctx, dt);
%     % This is the recursive fix
%     while again
%         [ctx, again, again_t] = ResampleTick(ctx, again_t);
%     end
%     ktick = ktick + 1;
%     if ktick == 200000
%         break;
%     end
%     
% end

% uvec = uvec(1:ktick, :);
% pvec = pvec(1:ktick-1, :);

% figure
% plot(uvec);
% ylim([-0.1, 1.1])

% v = [[0,0,0]; diff(pvec, 1, 1)];
% v = vecnorm(v, 2, 2)/dt;

figure
subplot(2,4,[1,2,5,6])
scatter3(pvec(:, 1), pvec(:, 2), pvec(:, 3), 1, vvec*60, 'o')
colormap jet
set(gca, 'Projection','orthographic')
% axis vis3d
% equal
xlabel('x')
ylabel('y')
zlabel('z')
colorbar

dcm_obj = datacursormode(gcf);
set(dcm_obj,'UpdateFcn',{@myupdatefcn,ctx, data})

ax(1) = subplot(2,4,3);
plot(uvec, vvec*60, 'b', uvec, fvec, 'r', uvec, cfvec, 'm')
title('Velocity in mm/min')
xlabel('Cumulative u')
legend('norm', 'Specified Feedrate', 'Max Constant Feedrate')
grid

ax(2) = subplot(2,4,4);
plot(uvec, avec)
title('Normalized acceleration in mm/s^2')
xlabel('Cumulative u')
legend('x', 'y', 'z')
ylim([-1.2 1.2])
grid

ax(3) = subplot(2,4,7);
plot(uvec, pvec)
title('Position')
xlabel('Cumulative u')
legend('x', 'y', 'z')
grid

ax(4) = subplot(2,4,8);
plot(uvec, jvec)
title('Normalized jerk in mm/s^3')
xlabel('Cumulative u')
ylim([-1.4 1.4])
legend('x', 'y', 'z')
grid


linkaxes(ax, 'x');
xlim([uvec(1) uvec(end)])

end

function txt = myupdatefcn(~, event_obj,ctx, data)
% Customizes text of data tips
pos = get(event_obj,'Position');
I = get(event_obj, 'DataIndex');
Curve = ctx.q_opt.get(data.kvec(I));
txt = {['X: ',num2str(pos(1))],...
       ['Y: ',num2str(pos(2))],...
       ['Z: ',num2str(pos(3))],...
       sprintf('%d: %d', data.kvec(I), I),...
       sprintf('%s (%s)', Curve.Type, Curve.zspdmode),...
       sprintf('u = %5.3f', data.uvec(I)),...
       sprintf('Vel : %3.0f%%', data.vvec(I)/Curve.FeedRate*100),...
       sprintf('Acc : %3.0f%%', max(abs(data.avec(I)))*100),...
       sprintf('Jerk: %3.0f%%', max(abs(data.jvec(I)))*100),...
       sprintf('F%d', int32(data.fvec(I))),...
       sprintf('L = %5.3f', LengthCurv(ctx, Curve, 0, 1)),...
       sprintf('GCode line: %d', Curve.gcode_source_line)};
end
