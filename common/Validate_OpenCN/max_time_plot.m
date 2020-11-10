function max_time_plot(ctx, tvec, vvec, fvec, avec, jvec)

% with vvec, avec and jvec calculated by CalcVAJ...

vvec_norm = vvec*60./fvec;      % vvec in [mm/s], fvec in [mm/min]
                                % fvec - specified feedrate (F code in gcode file)
                                % vvec_norm - normalized feedrate
avec = abs(avec./ctx.cfg.amax); % abs normalized
jvec = abs(jvec./ctx.cfg.jmax); % abs normalized

figure
plot(tvec, vvec_norm)
hold on
plot(tvec, avec)
hold on
plot(tvec, jvec)
title('Nomalized absolute vnorm, axyz, jxyz')
xlabel('time [s]')
xlim([0 tvec(end)]);
ylim([-0.2 1.2])
legend('vnorm', 'ax', 'ay', 'az', 'jx', 'jy', 'jz')
grid

end