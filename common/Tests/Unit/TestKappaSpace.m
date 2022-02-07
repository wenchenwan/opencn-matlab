clear; close all;


cfg = FeedoptDefaultConfig;
cfg.amax = [4,4,4];
% cfg.jmax = [2,8,8];
ctx = InitFeedoptPlan(cfg);

trafo = false;
A0 = zeros(3,1); A1 = A0; U0 = A0; U1 = A0;

Arc = ConstrHelixStruct(trafo, [0,0,0]', [1,1,0]', A0, A1, U0, U1, [0,0,1]',...
                        pi/2, [0,0,0]', 0, 1, ZSpdMode.NN);

u = kappaspace(ctx, Arc);

