function DestroyContext(ctx)
    ctx.q_gcode.delete();
    ctx.q_compress.delete();
    ctx.q_smooth.delete();
    ctx.q_split.delete();
    ctx.q_opt.delete();
    
    bspline_destroy(ctx.Bl);
    
    for k = 1:ctx.q_splines.size
        bspline_destroy(ctx.q_splines.get(k).sp.Bl);
    end
end