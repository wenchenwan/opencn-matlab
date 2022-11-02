function [ cfg ] = setMachineAxisInConfig( cfg, maskTot )
% setMachineAxisInConfig: Use maskTot to specify the axis used by the
% machine
% Inputs :
% cfg : The configuration structure
% maskTot : [ 1 x 6 ] logical vector [x,y,z,a,b,c]
% Outputs :
% cfg : The configuration structure
%#codegen

coder.inline("never");

assert( numel( maskTot ) == 6, "Error : maskTot should have 6 elements\n" );
cfg.maskTot = maskTot;

cfg = check_values( cfg );

end

function [ cfg ] = check_values( cfg )
    cfg.maskCart   = and( cfg.maskTot, logical( [ 1, 1, 1, 0, 0, 0 ] ) );
    cfg.maskRot    = and( cfg.maskTot, logical( [ 0, 0, 0, 1, 1, 1 ] ) );
    cfg.NumberAxis = int32( sum( cfg.maskTot ) );
    cfg.NCart      = int32( sum( cfg.maskCart ) );
    cfg.NRot       = cfg.NumberAxis - cfg.NCart;
    cfg.D          = ones(cfg.NumberAxis, 1);

    if( cfg.NCart > 0 )
        cfg.indCart = [ 1 : cfg.NCart ].';
    else
        cfg.indCart = 0;
    end

    if( cfg.NRot > 0 )
        cfg.indRot = [ 1 : cfg.NRot ].' + cfg.NCart;
        cfg.D(cfg.indRot) = cfg.coeffD;
    else
        cfg.indRot = 0;
    end        
end