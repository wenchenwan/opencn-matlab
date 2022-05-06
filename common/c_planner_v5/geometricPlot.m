function geometricPlot( ctx )
% geometricPlot :
% 
% Plot the geometric trajectory

N = 20;
u_vec = linspace(0, 1, N);

figure;
sizeGcode = ctx.q_gcode.size;
if sizeGcode
    dataGcode = zeros(3, sizeGcode *N);
    for i = 1:sizeGcode 
        Curve = ctx.q_gcode.get(i);
        
        [r0D, ~, ~, ~] = EvalCurvStruct( ctx, Curve, u_vec );
        dataGcode(:, N*(i-1)+1 : N*(i)) = r0D;
    end
    plot3(dataGcode(1, :), dataGcode(2, :), dataGcode(3, :));
    hold on
end

sizeComp = ctx.q_compress.size;
if sizeComp
    dataComp = zeros(3, sizeComp *N);
    for i = 1:sizeComp 
        Curve = ctx.q_compress.get(i);
        
        [r0D, ~, ~, ~] = EvalCurvStruct( ctx, Curve, u_vec );
        dataComp(:, N*(i-1)+1 : N*(i)) = r0D;
    end
    plot3(dataComp(1, :), dataComp(2, :), dataComp(3, :));
    hold on
end

sizeSmooth = ctx.q_smooth.size;
if sizeSmooth
    dataSmooth = zeros(3, sizeSmooth *N);
    for i = 1:sizeSmooth 
        Curve = ctx.q_compress.get(i);
        
        [r0D, ~, ~, ~] = EvalCurvStruct( ctx, Curve, u_vec );
        dataSmooth(:, N*(i-1)+1 : N*(i)) = r0D;
    end
    plot3(dataSmooth(1, :), dataSmooth(2, :), dataSmooth(3, :));
    hold on
end

sizeSplit = ctx.q_split.size;
if sizeSplit
    dataSplit = zeros(3, sizeSplit*N);
    for i = 1:sizeSplit
        Curve = ctx.q_split.get(i);
        
        [r0D, ~, ~, ~] = EvalCurvStruct( ctx, Curve, u_vec );
        dataSplit(:, N*(i-1)+1 : N*(i)) = r0D;
    end
    plot3(dataSplit(1, :), dataSplit(2, :), dataSplit(3, :));
    hold on
end

xlabel('x [mm]'); ylabel('y [mm]'); zlabel('z [mm]');
grid;
hold off

end