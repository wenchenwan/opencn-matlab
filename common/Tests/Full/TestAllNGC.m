function ctx = TestAllNGC
clear; clc;
global DebugConfig Ndone Ntotal

[SplitList, CutList] = meshgrid(logspace(0, 1, 10), logspace(-1, 0, 10));

cfg = FeedoptDefaultConfig;
% cfg.NDiscr = 200;
% cfg.NBreak = 100;
% cfg.NHorz = 3;
% DefaultConfig = cfg;
% SplitList = 10;
% CutList = 10;

SplitList = SplitList(:);
CutList = CutList(:);

ngc_unit_list = string(fullfile('ngc_test/unit', {dir('ngc_test/unit/*.ngc').name}));
ngc_full_list = string(fullfile('ngc_test/full', {dir('ngc_test/full/*.ngc').name}));

ngc_list = [ngc_unit_list];

Ntotal = numel(ngc_list) * numel(CutList);
Ndone = 0;

DebugConfig = 0;
EnableDebugLog(DebugCfg.Warning);
EnableDebugLog(DebugCfg.Error);
EnableDebugLog(DebugCfg.OptimProgress);

% diary test_ngc.log
% 
tic
cfg.source = char(ngc_full_list(1));
% cfg.source = char('ngc_test/spline_osc_2.ngc');
% cfg.source = char('ngc_test/full/Ebauche_3axes_V01.nc');
cfg.NDiscr = 20;
cfg.NBreak = 10;
cfg.NHorz = 5;
% cfg.amax = repmat(1e10, 1, 3);
% cfg.jmax = repmat(1e10, 1, 3);
cfg.SkipCompressing = false;
ctx = InitFeedoptPlan(cfg);
ctx = FeedoptPlanRun(ctx);
toc


PlotResampled(ctx, 1e-3)


% % prob: 5
% for kngc = 1:length(ngc_list)
%     ngc = ngc_list(kngc);
% 
% %     prob: 7
%     for ksplit = 1:length(SplitList)
%         Cut = CutList(ksplit);
%         Split = SplitList(ksplit);
%         fprintf('CONFIG: CutOff = %f, LSplit = %f, ngc = %s\n', Cut, Split, ngc);
%         drawnow('update')
% 
%         cfg = FeedoptDefaultConfig;
%         cfg.LSplit = Split;
%         cfg.CutOff = Cut;
%         cfg.NDiscr = 20;
%         cfg.NBreak = 10;
%         cfg.source = char(ngc);
% 
%         ctx = InitFeedoptPlan(cfg);
%         ctx = FeedoptPlanRun(ctx);
%         send(D, 1);
%     end
% end
% toc

diary off

end
function nUpdateWaitbar(~)
global Ndone Ntotal fwait
Ndone = Ndone + 1;
msg = sprintf('Testing, %d/%d done', Ndone, Ntotal);
waitbar(Ndone/Ntotal, fwait, msg);
end

