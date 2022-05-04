function PlotCurvStructs(ctx, CurvStructs)

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

ktick = 1;
N = length(CurvStructs);

Nu = 20;
u = linspace(0, 1, Nu);

for k = 1:N
    Curv = CurvStructs(k);
    [r0D, ~, ~, ~] = EvalCurvStruct(ctx, Curv, u);
    uvec(ktick:(ktick + Nu - 1)) = u;
    pvec(ktick:(ktick + Nu - 1), :) = r0D.';
    kvec(ktick:(ktick + Nu - 1)) = k;
    ktick = ktick + Nu;
    
    if ktick > 200000
        warning('Breaking because ktick > 200000')
        break;
    end
end

ktick = ktick - 1;

uvec = uvec(1:ktick);
pvec = pvec(1:ktick, :);
kvec = kvec(1:ktick);

data = table(uvec, kvec);


figure
% subplot(2,4,[1,2,5,6])
plot3(pvec(:, 1), pvec(:, 2), pvec(:, 3))
colormap jet
set(gca, 'Projection','orthographic')
% axis vis3d
% equal
xlabel('x')
ylabel('y')
zlabel('z')
% colorbar
grid

dcm_obj = datacursormode(gcf);
set(dcm_obj, 'UpdateFcn', {@myupdatefcn, ctx, CurvStructs, data})
% 
% ax(1) = subplot(2,4,3);
% plot(uvec, vvec*60, 'b', uvec, fvec, 'r', uvec, cfvec, 'm')
% title('Velocity in mm/min')
% xlabel('Cumulative u')
% legend('norm', 'Specified Feedrate', 'Max Constant Feedrate')
% grid
% 
% ax(2) = subplot(2,4,4);
% plot(uvec, avec)
% title('Normalized acceleration in mm/s^2')
% xlabel('Cumulative u')
% legend('x', 'y', 'z')
% ylim([-1.2 1.2])
% grid
% 
% ax(3) = subplot(2,4,7);
% plot(uvec, pvec)
% title('Position')
% xlabel('Cumulative u')
% legend('x', 'y', 'z')
% grid
% 
% ax(4) = subplot(2,4,8);
% plot(uvec, jvec)
% title('Normalized jerk in mm/s^3')
% xlabel('Cumulative u')
% ylim([-1.4 1.4])
% legend('x', 'y', 'z')
% grid
% 
% 
% linkaxes(ax, 'x');
% xlim([uvec(1) uvec(end)])

end

function txt = myupdatefcn(~, event_obj, ctx, CurvStructs, data)
% Customizes text of data tips
pos = get(event_obj,'Position');
I = get(event_obj, 'DataIndex');
Curve = CurvStructs(data.kvec(I));
txt = {['X: ',num2str(pos(1))],...
       ['Y: ',num2str(pos(2))],...
       ['Z: ',num2str(pos(3))],...
       sprintf('%d: %d', data.kvec(I), I),...
       sprintf('%s (%s)', Curve.Info.Type, Curve.Info.zspdmode),...
       sprintf('u = %5.3f', data.uvec(I)),...
       sprintf('L = %5.3f', LengthCurv(ctx, Curve, 0, 1)),...
       sprintf('GCode line: %d', Curve.gcode_source_line)};
%        sprintf('Vel : %3.0f%%', data.vvec(I)/Curve.FeedRate*100),...
%        sprintf('Acc : %3.0f%%', max(abs(data.avec(I)))*100),...
%        sprintf('Jerk: %3.0f%%', max(abs(data.jvec(I)))*100),...
%        sprintf('F%d', int32(data.fvec(I))),...

end
