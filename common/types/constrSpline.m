function [ SplineStrct ] = constrSpline( coeff, knots, BlStruct ) %#codegen
% Construct a struct for the spline.
% 
% Inputs :
% BlStruct     : Base Spline structure
% coeff        : [ NDim x ncoeff ] Coefficient of the spline
% knots        : Knots of the spline
% Other fields:
% Ltot         : Total length of the spline
% Lk           : Individual length between two knots
%
% Outputs :
% SplineStrct    : The resulting structure

SplineStrct = struct( ...
                    'Bl', BlStruct,...
                    'coeff', coeff,...
                    'knots', knots,...
                    'Ltot', 0.0, ...
                    'Lk', knots...
                    );

if ~coder.target( 'MATLAB' )
    coder.varsize( 'SplineStrct.Lk',    StructTypeName.dimLk{ : } );
    coder.varsize( 'SplineStrct.coeff', StructTypeName.dimCoeffs{ : } );
    coder.varsize( 'SplineStrct.knots', StructTypeName.dimKnots{ : } );
    coder.cstructname( SplineStrct.Bl, StructTypeName.BaseSpline );
    coder.cstructname( SplineStrct, StructTypeName.Spline );
end


end