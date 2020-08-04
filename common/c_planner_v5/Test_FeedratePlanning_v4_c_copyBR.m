
clear; clc; close all;

load('EbaucheSplineOscillations.mat');

sp = ctx.q_splines.get(1);

knots = sp.knots(4:end-3);

pvec = zeros(3, length(knots));

for i=1:length(knots)
    
    pvec(:,i) = spval(sp,knots(i));
    
end

figure(1)
%subplot(1,2,1);
plot3(pvec(1,:), pvec(2,:), pvec(3,:), '-xr');
hold on

L=SplineLengthApproxSP(sp, 0, 1);


cfg = FeedoptDefaultConfig();

cfg.source = 'ngc_test/full/003_micro5_3axes_ebauche.ngc';

ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);

compress_end = ctx.q_compress.size();

L_all = zeros(1, compress_end);

for i=1:compress_end
    
    Curv = ctx.q_compress.get(i);
    
    if Curv.Type==CurveType.Spline
        L_all(i)=LengthCurv(ctx, Curv, 0, 1);
    else
        L_all(i)=0;
    end
        
end

figure(2)
stem(L_all)
xlabel('compress spline nr');
ylabel('spline length [mm]');
hold on

plot([1, compress_end], [L, L], '-g');
hold off

Curv = ctx.q_compress.get(30139);

figure(1)
%subplot(1,2,2);
PlotCurvStructs(ctx, Curv);
hold off

line_number = Curv.gcode_source_line;
