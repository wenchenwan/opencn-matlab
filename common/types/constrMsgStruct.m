function [ CStruct ] = constrMsgStruct( msg ) 
%#codegen
% Construct a struct containing char msg.
% 
% Inputs :
% msg     : Char array to store the msg
% 
% Outputs :
% CStruct       : The resulting structure
dim         = StructTypeName.dimMsg{1};
msgDefault  = repmat( '0', dim ); 
l           = length( msg );

if( l > dim( 2 ) ), l = dim( 2 ); end

CStruct = struct(   'msg',  msgDefault, ...
                    'size', l ...
                    );
CStruct.msg( 1 : l )    = msg( 1 : l );
CStruct.msg( end )      = '0';
coder.cstructname( CStruct, StructTypeName.Msg );

end