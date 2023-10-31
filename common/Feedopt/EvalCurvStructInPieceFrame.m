function [r0D, r1D, r2D, r3D] = EvalCurvStructInPieceFrame( ctx, curv, u_vec )
%#codegen
coder.inline("never");

% Detect cusp in piece frame
[r0D, r1D, r2D, r3D]= EvalCurvStruct( ctx, curv, u_vec );

if( ~curv.Info.TRAFO )
    % Aply Kinematic transform
    ctx.kin.set_tool_length( curv.tool.offset.z );
    [r0D, r1D, r2D, r3D] = ctx.kin.relative(r0D, r1D, r2D, r3D);
end

end