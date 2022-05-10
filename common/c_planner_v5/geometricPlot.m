function geometricPlot( ctx )
% geometricPlot :
% 
% Plot the geometric trajectory

N = 20;
u_vec = linspace(0, 1, N);

sizeGcode = ctx.q_gcode.size;
if sizeGcode
    dataGcode = zeros(ctx.cfg.NumberAxis, sizeGcode *N);
    for i = 1:sizeGcode 
        Curve = ctx.q_gcode.get(i);
        
        [r0D, ~, ~, ~] = EvalCurvStruct( ctx, Curve, u_vec );
        dataGcode(:, N*(i-1)+1 : N*(i)) = r0D;
    end
    plot5Axis([dataGcode(1, :); dataGcode(2, :); dataGcode(3, :);...
               dataGcode(4, :); dataGcode(5, :)], 1, 10);
end

sizeComp = ctx.q_compress.size;
if sizeComp
    dataComp = zeros(ctx.cfg.NumberAxis, sizeComp *N);
    for i = 1:sizeComp 
        Curve = ctx.q_compress.get(i);
        
        [r0D, ~, ~, ~] = EvalCurvStruct( ctx, Curve, u_vec );
        dataComp(:, N*(i-1)+1 : N*(i)) = r0D;
    end
    plot5Axis([dataComp(1, :); dataComp(2, :); dataComp(3, :);...
               dataComp(4, :); dataComp(5, :)], 1, 10);
end

sizeSmooth = ctx.q_smooth.size;
if sizeSmooth
    dataSmooth = zeros(ctx.cfg.NumberAxis, sizeSmooth *N);
    for i = 1:sizeSmooth 
        Curve = ctx.q_compress.get(i);
        
        [r0D, ~, ~, ~] = EvalCurvStruct( ctx, Curve, u_vec );
        dataSmooth(:, N*(i-1)+1 : N*(i)) = r0D;
    end
    plot5Axis([dataSmooth(1, :); dataSmooth(2, :); dataSmooth(3, :);...
               dataSmooth(4, :); dataSmooth(5, :)], 1, 10);
end

sizeSplit = ctx.q_split.size;
if sizeSplit
    dataSplit = zeros(ctx.cfg.NumberAxis, sizeSplit*N);
    for i = 1:sizeSplit
        Curve = ctx.q_split.get(i);
        
        [r0D, ~, ~, ~] = EvalCurvStruct( ctx, Curve, u_vec );
        dataSplit(:, N*(i-1)+1 : N*(i)) = r0D;
    end
    plot5Axis([dataSplit(1, :); dataSplit(2, :); dataSplit(3, :);...
               dataSplit(4, :); dataSplit(5, :)], 1, 10);
end

end