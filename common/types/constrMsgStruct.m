function [ CStruct ] = constrMsgStruct( msg ) 
%#codegen
% Construct a struct containing char msg.
% 
% Inputs :
% msg     : Char array to store the msg
% 
% Outputs :
% CStruct       : The resulting structure
msgChar     = char( msg );
dim         = StructTypeName.dimMsg{ 1 };
msgDefault  = repmat( '0', dim ); 
l           = length( msgChar );

if( l > dim( 2 ) ), l = dim( 2 ); end

CStruct = struct(   'msg',  msgDefault, ...
                    'size', l ...
                    );

CStruct.msg( 1 : l )    = msgChar( 1 : l );
CStruct.msg( l )        = '0';
coder.cstructname( CStruct, StructTypeName.Msg );

end
