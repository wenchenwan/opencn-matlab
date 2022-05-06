
if ~exist('ctx', 'var')
    warning('Could not find variable ctx, SaveTransition is ignored')
    return;
end


if ~exist('CurvStruct1', 'var')
    warning('Could not find variable CurvStruct1, SaveTransition is ignored')
end


if ~exist('CurvStruct2', 'var')
    warning('Could not find variable CurvStruct2, SaveTransition is ignored')
end

do_save(ctx, CurvStruct1, CurvStruct2)

function do_save(ctx, CurvStruct1, CurvStruct2)
    cfg = ctx.cfg;
    source_name = split(cfg.source, '/');
    filename = sprintf('Transition_%s_%d-%d.mat', ...
        source_name{end}, ...
        CurvStruct1.gcode_source_line,...
        CurvStruct2.gcode_source_line);
    
    
    save(filename, 'cfg', 'CurvStruct1', 'CurvStruct2');
    if CurvStruct1.Info.Type == CurveType.Spline
        Spline1 = ctx.q_spline.get(CurvStruct1.sp_index);
        save(filename, '-append', 'Spline1');
    end
    
    if CurvStruct2.Info.Type == CurveType.Spline
        Spline2 = ctx.q_spline.get(CurvStruct2.sp_index);
        save(filename, '-append', 'Spline2');
    end
end