function [r_cart ,r_rot] = SplitCartRot(ctx, r) %#codegen
% SplitCartRot
%
% Input 
% ctx       : Context structure
% r         : Point to split
% 
% Output
% r_cart    : Cartesian part of r
% r_rot     : Rotativ part of r
%

NCart = ctx.cfg.NCart;
NRot = ctx.cfg.NRot;
indCart = ctx.cfg.indCart;
indRot = ctx.cfg.indRot;

[~, l] = size(r);

r_cart = zeros(NCart, l);
r_rot = zeros(NRot, l);

for i = 1:NCart
    r_cart(i, :) = r(indCart(i), :);
end
for i = 1:NRot
    r_rot(i, :) = r(indRot(i), :);
end

end