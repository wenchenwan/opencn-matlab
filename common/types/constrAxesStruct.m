function [ CStruct ] = constrAxesStruct( x, y, z, a, b, c, u, v, w ) 
%#codegen
% Construct a struct containing axes information.
% 
% Inputs :
% x     : Axis X
% y     : Axis Y
% z     : Axis Z
% a     : Axis A
% b     : Axis B
% c     : Axis C
% u     : Axis U
% v     : Axis V
% w     : Axis W
% 
% Outputs :
% CStruct       : The resulting structure

CStruct = struct(   'x', x, ...
                    'y', y, ...
                    'z', z, ...
                    'a', a, ...
                    'b', b, ...
                    'c', c, ...
                    'u', u, ...
                    'v', v, ...    
                    'w', w ...       
                );

coder.cstructname( CStruct, StructTypeName.Axes );

end