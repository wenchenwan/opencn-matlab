function [r0D, r1D, r2D, r3D] = EvalCurvStructInPieceFrame( ctx, curv, u_vec )
%#codegen
coder.inline("never");

% Detect cusp in piece frame
trafo_flag          = curv.Info.TRAFO;
curv.Info.TRAFO     = true;

[r0D, r1D, r2D, r3D]= EvalCurvStruct( ctx, curv, u_vec );

curv.Info.TRAFO     = trafo_flag;
end