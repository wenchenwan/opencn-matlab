function ctx = SplitCurvStructs(ctx)

if ctx.q_smooth.isempty()%ctx.q_smooth.isempty() IL FAUDRA REMETTRE Q_SMOOTH
    return;
end

N = ctx.q_smooth.size;

DebugLog(DebugCfg.Validate, 'Splitting...\n');
DebugLog(DebugCfg.OptimProgress, 'Splitting...\n');

for k = 1:N
    CurvStruct = ctx.q_smooth.get(k);
%     CurvStruct.Info.Type
%     CurvStruct.R0'
%     CurvStruct.R1'
    ctx = SplitCurvStruct(ctx, CurvStruct);
end

% Check_zspdmode(ctx); WIP

end

% function Check_zspdmode(ctx) WIP
% 
%     % Check of the zspdmode
%     zspmodevec = zeros(1, sizeSplit);
% 
%     Curv1 = ctx.q_split.get(1);
%     Curv2 = ctx.q_split.get(1);
% 
%     if Curv1.Info.zspdmode ~= ZN
%         
%     end
% 
%     for i = 1:sizeSplit
%         Curv2 = ctx.q_split.get(i);      % Get Curv in the queue
%         Curv.Info.zspdmode
%         zspmodevec(i) = Curv.Info.zspdmode;
%     end
% 
%     assert( all( diff_r ), mfilename + ...
%                         ".m : continuity speed failed " + mat2str( diff_r' ) );
% 
% end