function Merge_Partiel
%
close all;
%% kinematic constraints
vmax   = 150;              % max feedrate in [mm/s]
amax   = 20e3*ones(3, 1);  % max acceleration per axis [mm/s^2]
jmax   = 1.5e10*ones(3, 1); % max jerk per axis [mm/s^3]

% vmax   = 1.5;              % max feedrate in [m/s]
% amax   = 4.5*ones(3, 1);   % max acceleration per axis [m/s^2]
% jmax   = 100*ones(3, 1);   % max jerk per axis [m/s^3]

%% geometry
load('.\GeomFiles\SmallAnchor2D_F9000_CS.mat');
% load('.\GeomFiles\PieceDemoLinuxCNC_Compressing0_035_CS.mat');
CurvStructs0 = CurvStructs;
Stats_CrvStrc(CurvStructs);

%% smoothing of transitions
CutOff      = 0.1;   
CurvStructs1 = SmoothCurvStructs(CurvStructs0, CutOff);
%
%% splitting (in order to homogenize length of curve pieces)
L_split     = 8; % 0.5; % 8; 
CurvStructs2 = SplitCurvStructs(CurvStructs1, L_split);

cfg = FeedoptDefaultConfig;
ctx = InitFeedoptPlan(cfg);

%% plot curve pieces
PlotCurvStructs_v4(ctx, CurvStructs0, CurvStructs2);
