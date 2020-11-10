function [status, ratioTOpt] = FoptVerif(ctx, uvec, v_tol, a_tol, j_tol, TOpt_tol)

status = 0;         % Success default
ratioTOpt = 0;

if isempty(uvec)
    bitset(status, 5);
    return;
end

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
     if v_norm/vmax > 1+v_tol
         
         bitset(status, 1);
         
     end
     
     if any(abs(acc'./ctx.cfg.amax) > 1+a_tol)
         
         bitset(status, 2);
         
     end
     
     if any(abs(jerk'./ctx.cfg.jmax) > 1+j_tol)
         
         bitset(status, 3);
         
     end
     
     
     % time-optimality verif     
     condv = v_norm/vmax > 1-v_tol;
       
     conda = any(abs(acc'./ctx.cfg.amax) > 1-a_tol);
     
     condj = any(abs(jerk'./ctx.cfg.jmax) > 1-j_tol);
     
     if any([condv, conda, condj])
         
        t_max = t_max + ctx.cfg.dt;
        
     end
     
end

    ratioTOpt = t_max/t_tot;
    if ratioTOpt < TOpt_tol
        bitset(status, 4);
    end

end