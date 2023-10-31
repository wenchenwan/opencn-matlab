function [ params ] = paramsDefaultMsg( ~ ) %#codegen
% paramsDefaultAxes : Get default params for the msg struct.

msg         = repmat( char(0), 1, StructTypeName.dimMsg{1}(2) );

if( coder.target( 'MATLAB' ) )
    params = { msg };
else
    params.msg     = msg;
end

end