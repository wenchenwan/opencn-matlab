function [ queue ] = checkTrafo( ctx, queue )
% checkTrafo : Handle a trafro command sent in middle of a Gcode
% Note : this script is still experimental
N = double( queue.size );

prevTrafo = queue.get( 1 ).Info.TRAFO;

for j = 2 : N
    CurvStruct = queue.get( j );
    if( prevTrafo ~= CurvStruct.Info.TRAFO )
        disp( "trafo changed : line " + CurvStruct.Info.gcode_source_line );
        
        ctx.kin = ctx.kin.set_tool_length( CurvStruct.Tool.offset.z );

        if( CurvStruct.Info.TRAFO  )
            CurvStruct.R0( ctx.cfg.maskTot ) = ctx.kin.r_relative( CurvStruct.R0( ctx.cfg.maskTot ) );
        else
            CurvStruct.R0( ctx.cfg.maskTot ) = ctx.kin.r_joint( CurvStruct.R0( ctx.cfg.maskTot ) );
        end
        queue.set( j, CurvStruct );
    end

    prevTrafo = CurvStruct.Info.TRAFO;
end

end