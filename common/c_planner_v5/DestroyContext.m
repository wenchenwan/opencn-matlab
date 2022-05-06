function DestroyContext(ctx)
    ctx.q_gcode.delete();
    ctx.q_compress.delete();
    ctx.q_smooth.delete();
    ctx.q_split.delete();
    ctx.q_opt.delete();
    
    bspline_destroy(ctx.Bl);
    
%     if coder.target('rtw') || coder.target('mex')
        for k = 1:ctx.q_spline.size
            bspline_destroy(ctx.q_spline.get(k).sp.Bl);
        end
%     end
    
    ctx.q_spline.delete();
    
end