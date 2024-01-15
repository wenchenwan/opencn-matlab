function ctx = splitQueue( ctx )
%#codegen
% splitQueue : Split the curves in the q_smooth queue.
%
% Inputs :
%   ctx : The context of the computational chain.
% Outputs : 
%   ctx : The context of the computational chain.
%

if ctx.q_smooth.isempty(), return; end
ctx.k0 = int32( 1 );
DebugLog( DebugCfg.Validate,        'Splitting...\n' );
DebugLog( DebugCfg.OptimProgress,   'Splitting...\n' );


N = ctx.q_smooth.size;

for k = 1 : N
    ocn_print( ctx.cfg.ENABLE_PRINT_MSG, "" + ctx.k0 + "/" + N, mfilename );
    ctx.k0  = ctx.k0 + 1;


    ctx     = splitCurvStruct( ctx, ctx.q_smooth.get( k ) );
end

end
