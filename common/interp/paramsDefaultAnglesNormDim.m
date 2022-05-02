function [ params ] = paramsDefaultAnglesNormDim( ~ ) %#codegen
% paramsDefaultAnglesNormDim : Get default params for angles norm Din.

A0_deg  = zeros( 1, 1 );
A1_deg  = zeros( 1, 1 );
A1_mode = ones( 1, 1 ) * AngleMode.CCW ;
G90     = false;

if( coder.target( 'MATLAB' ) && nargin > 0 )
    A0_deg = coder.typeof(  A0_deg, StructTypeName.dimADeg{ : } );
    A1_deg = coder.typeof(  A1_deg, StructTypeName.dimADeg{ : } );
    A1_mode = coder.typeof( A1_mode, StructTypeName.dimADeg{ : } );
end

params = { A0_deg, A1_deg, A1_mode, G90 };

end