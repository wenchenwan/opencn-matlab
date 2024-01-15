function [r0D, r1D, r2D, r3D] = EvalCurvStructInPieceFrame( ctx, curv, u_vec )
%#codegen
% EvalCurvStructInPieceFrame : Eval curve structure and its derivatives on 
% a set of u points on the piece frame (WCS).
%
% Inputs : 
% ctx   : The context of the computational chain
% curv  : The curve used in the evaluation
% u_vec : U vectors.
%
% Outputs : 
% r0D   : Matrix of points for a given set of u values
% r1D   : Matrix of points (first derivative) for a given set of u values
% r2D   : Matrix of points (second derivative) for a given set of u values
% r3D   : Matrix of points (third derivative) for a given set of u values
%
coder.inline("never");

% Detect cusp in piece frame
[r0D, r1D, r2D, r3D]= EvalCurvStruct( ctx, curv, u_vec );

if( ~curv.Info.TRAFO )
    % Aply Kinematic transform
    ctx.kin.set_tool_length( -curv.tool.offset.z );
    [r0D, r1D, r2D, r3D] = ctx.kin.relative(r0D, r1D, r2D, r3D);
end

end
