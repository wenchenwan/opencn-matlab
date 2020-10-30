function [status, ratioTOpt] = FoptVerif(ctx, uvec, v_tol, a_tol, j_tol, TOpt_tol)

status = 1;         % Success default

% machining time
t_tot = (size(uvec, 1)-1)*ctx.cfg.dt;

t_max = 0;

for k=2:size(uvec, 1)
    
    ucum = uvec(k);
    u = ucum - floor(ucum);
    
    Curv = ctx.q_opt.get(ceil(ucum));
    
    vmax = Curv.FeedRate;
    
     [v_norm, acc, jerk] =...
            CalcVAJ(ctx, Curv, ctx.Bl, u);
     
     % constraints respect verif
     if (v_norm > vmax+vmax*v_tol) ||...
        any(abs(acc') > ctx.cfg.amax+ctx.cfg.amax*a_tol) ||...
        any(abs(jerk') > ctx.cfg.jmax+ctx.cfg.jmax*j_tol)
        
        status = 0;
    
     end
     
     % time-optimality verif
     condv = (v_norm > vmax - vmax*v_tol) && (v_norm < vmax + vmax*v_tol);
       
     conda = any((abs(acc') > ctx.cfg.amax - ctx.cfg.amax*a_tol) &...
         (abs(acc') < ctx.cfg.amax + ctx.cfg.amax*a_tol));
     
     condj = any((abs(jerk') > ctx.cfg.jmax - ctx.cfg.jmax*j_tol) &...
         (abs(jerk') < ctx.cfg.jmax + ctx.cfg.jmax*j_tol));
     
     if any([condv, conda, condj])
         t_max = t_max + ctx.cfg.dt;
     end
     
end

    ratioTOpt = t_max/t_tot;
    if ratioTOpt < TOpt_tol
        status = 0;
    end

end