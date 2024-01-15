function [ copy ] = bspline_copy( Bl ) %#codegen
% bspline_copy : Copy the bspline bases
% Inputs :
% Bl            : BSpline bases
% Outputs :
% Copy          : Copy of the BSpline bases
coder.inline("never");
copy = bspline_create( Bl.order, Bl.breakpoints );
end
