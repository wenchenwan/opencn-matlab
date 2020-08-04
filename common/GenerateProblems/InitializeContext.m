function ctx = InitializeContext(cfg)
%#codegen
ctx.values = zeros(cfg.dim1, cfg.dim2);
ctx.counter = int32(0);
coder.varsize('ctx.values', [20, 10], [1,1]);
coder.cstructname(ctx, 'Context');
end