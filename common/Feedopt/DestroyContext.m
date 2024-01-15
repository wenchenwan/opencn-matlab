function DestroyContext( ctx )
    % DestroyContext : Destroy context of the computational chain. The
    % memory stored in the queue are relased.
    %
    % Inputs :
    % Ctx   : Context of the computational chain
    %

    ctx.q_gcode.delete();
    ctx.q_compress.delete();
    ctx.q_smooth.delete();
    ctx.q_split.delete();
    ctx.q_opt.delete();
    
    bspline_destroy(ctx.Bl);
    
    for k = 2 : ctx.q_spline.size
        bspline_destroy( ctx.q_spline.get(k).sp.Bl );
    end
    
    ctx.q_spline.delete();
end
