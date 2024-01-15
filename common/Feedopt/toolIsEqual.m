function [ isEqual ] = toolIsEqual( tool1, tool2 ) 
%#codegen
% toolIsEqual : Check if the tools are equal or not.
% 
% Inputs :
%   tool1       : First tool.
%   tool2       : Second tool.
%
% Outputs : 
%   isEqual     : Boolean value. TRUE means tools are equals.
%

% Check the tools are equals
isEqual = false;

if( tool1.toolno        ~= tool2.toolno ),          return; end
if( tool1.pocketno      ~= tool2.pocketno ),        return; end
if( tool1.diameter      ~= tool2.diameter ),        return; end
if( tool1.frontangle    ~= tool2.frontangle ),      return; end
if( tool1.backangle     ~= tool2.backangle ),       return; end
if( tool1.orientation   ~= tool2.orientation ),     return; end
if( tool1.offset.x      ~= tool2.offset.x ),        return; end
if( tool1.offset.y      ~= tool2.offset.y ),        return; end
if( tool1.offset.z      ~= tool2.offset.z ),        return; end
if( tool1.offset.a      ~= tool2.offset.a ),        return; end
if( tool1.offset.b      ~= tool2.offset.b ),        return; end
if( tool1.offset.c      ~= tool2.offset.c ),        return; end
if( tool1.offset.u      ~= tool2.offset.u ),        return; end
if( tool1.offset.v      ~= tool2.offset.v ),        return; end
if( tool1.offset.w      ~= tool2.offset.w ),        return; end

isEqual = true;
end
