
% gcode_begin = 1;
% gcode_end = ctx.q_gcode.size;
% 
% ctx = CompressCurvStructs(ctx);
% ctx = SmoothCurvStructs(ctx);
% ctx = SplitCurvStructs(ctx);

CurvCompress = ctx.q_compress.getall();
CurvSmooth = ctx.q_smooth.getall();
CurvSplit = ctx.q_split.getall();

figure (1)
% pvec = PlotCurvStructsBR(ctx, CurvStructs, gcode_begin, gcode_end);
% plot3(pvec(1,:), pvec(2,:), pvec(3,:), 'b');
% hold on
% 
% 
% compress_begin = 1;
% compress_end = ctx.q_compress.size;
% pvec = PlotCurvStructsBR(ctx, CurvCompress, compress_begin, compress_end);
% plot3(pvec(1,:), pvec(2,:), pvec(3,:), 'g');
% hold on
% % 
% smooth_begin = 1;
% smooth_end = ctx.q_smooth.size;
% pvec = PlotCurvStructsBR(ctx, CurvSmooth, smooth_begin, smooth_end);
% plot3(pvec(1,:), pvec(2,:), pvec(3,:), 'b');
% hold on

split_begin = 1;
split_end = ctx.q_split.size;
pvec = PlotCurvStructsBR(ctx, CurvSplit, split_begin, split_end);
plot3(pvec(1,:), pvec(2,:), pvec(3,:), '-xg');
hold on


