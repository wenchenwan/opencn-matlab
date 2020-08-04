clc; clear; close all;

L = 2;   % lines length [mm]
R = 1e-4; % arc radius [mm]
NSegm_G01 = 65; % number of small lines
dL = 0.28; % line length in X direction [mm]
Aosc = 0.001; % osc amplitude [mm]
     
cfg = FeedoptDefaultConfig();
cfg.LSplit = 100; % we do not split the geometry
dt=100e-6; % initial resampling period [s]
ctx = InitFeedoptPlan(cfg);

%% Geometry construction (BEGIN) %%%%%%%%%%%%%%%%%%%%%

Line1 = ConstrLineStruct([0, 0, 0]', [L, 0, 0]', 100, ZSpdMode.ZN);
ctx.q_gcode.push(Line1);


% oscillation pattern construction

for k=1:NSegm_G01
    
    if k==1
        P0 = [  L+(k-1)*dL;
                0;
                0];
    else
        P0 = [  L+(k-1)*dL;
                0;
                ((-1)^(k+1))*Aosc];
    end
    
    if k==NSegm_G01
        P1 = [  L+k*dL;
                0;
                0];
    else
        P1 = [  L+k*dL;
                0;
                ((-1)^k)*Aosc];
    end
    
    Line = ConstrLineStruct(P0, P1, 100, ZSpdMode.NN);
    ctx.q_gcode.push(Line);
    
end

Line2 = ConstrLineStruct(P1, [P1(1)+L, 0, 0]', 100, ZSpdMode.NN);
ctx.q_gcode.push(Line2);

Arc = ConstrHelixStructFromArcFeed(P1(1)+L, 0, 0, P1(1)+L+R, R, 0, P1(1)+L, R, 0, 1, [0 0 1]');
ctx.q_gcode.push(Arc);

Line3 = ConstrLineStruct([P1(1)+L+R, R, 0]', [P1(1)+L+R, L+R, 0]', 100, ZSpdMode.NZ);
ctx.q_gcode.push(Line3);

%% Geometry construction (END) %%%%%%%%%%%%%%%%%%%%%


ctx = FeedoptPlanRun(ctx);

PlotResampled(ctx, dt);
