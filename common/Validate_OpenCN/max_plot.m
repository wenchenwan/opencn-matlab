function max_plot(ctx, pvec, vvec, fvec, avec, jvec)

% with vvec, avec and jvec calculated by CalcVAJ...

vvec_norm = vvec*60./fvec;      % vvec in [mm/s], fvec in [mm/min]
                                % fvec - specified feedrate (F code in gcode file)
                                % vvec_norm - normalized feedrate
avec = abs(avec./ctx.cfg.amax); % abs normalized
jvec = abs(jvec./ctx.cfg.jmax); % abs normalized

max_vec = zeros(length(vvec_norm), 1);  % Preallocation

% max_vec: max param among 7 (vnorm, ax, ay, az, jx, jy, jz)
% at each time tick
for k=1:length(vvec_norm)
    vec = [ vvec_norm(k), avec(k, :), jvec(k, :) ];
    max_vec(k) = max(vec);
end

figure
scatter(pvec(:, 1), pvec(:, 2), 1, max_vec, 'o')
colormap jet
title('Maximum parameter, absolute value, normalized')
xlabel('x')
ylabel('y')
colorbar

end