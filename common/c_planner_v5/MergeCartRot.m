function [out] = MergeCartRot(ctx, cart, rot) %#codegen
% MergeCartRot
% 

NCart = ctx.cfg.NCart;
NRot = ctx.cfg.NRot;
indCart = ctx.cfg.indCart;
indRot = ctx.cfg.indRot;
Ntot = NCart+NRot;

[~, l] = size(cart);

out = zeros(Ntot, l);

for i = 1:NCart
    out(indCart(i), :) = cart(i, :);
end
for i = 1:NRot
    out(indRot(i), :) = rot(i, :);
end

end