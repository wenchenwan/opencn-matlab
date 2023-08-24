function [ CStruct ] = constrToolStruct( toolno, pocketno, offset, ...
    diameter, frontangle, backangle, orientation) %#codegen
% Construct a struct containing the information from the Gcode.
% 
% Inputs :
% toolno        : Tool number
% pocketno      : Pocket number used to store the tool
% offset        : Struct used to store the axes offset
% diameter      : Diameter of the tool
% frontangle    : Frontangle of the tool
% backangle     : Backangle of the tool
% orientation   : Orientation of the tool
% 
% Outputs :
% CStruct       : The resulting structure
coder.inline("never");

CStruct = struct(   'toolno',       toolno, ...
                    'pocketno',     pocketno, ...
                    'offset',       offset, ...
                    'diameter',     diameter, ...
                    'frontangle',   frontangle, ...
                    'backangle',    backangle, ...
                    'orientation',  orientation ...
                );

if ~coder.target( 'MATLAB' )
    coder.cstructname( CStruct.offset,  StructTypeName.Axes );
    coder.cstructname( CStruct,         StructTypeName.Tool );
end

end