clear; close all;

cfg = FeedoptDefaultConfig;
cfg.amax = [4,4,4];
% cfg.jmax = [2,8,8];
ctx = InitFeedoptPlan(cfg);

trafo = false; % TRAFO flag disable 
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

P0 = zeros(3, 1); P1 = [1, 1, 0]';
Cprim = [0,0,1]'; delta = 0; evec = [0,0,0]'; theta = 0; pitch = 1; 
mode = ZSpdMode.NN; FeedRate = 1;

Arc = ConstrHelixStruct(trafo,...
                      Poff, Aoff, Uoff, Doff, P0, P1, A0, A1, U0, U1, ...
                      Cprim, delta, evec, theta, pitch, FeedRate, mode);

GetCurvMaxFeedrate(ctx, Arc)