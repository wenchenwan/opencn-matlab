function [PStrct] = ConstrProfileStruct( dim )
% ConstrProfileStruct : Construct a structure of type profile. This
% structure is filled after the resampling.
dim         = int32( dim );
u_def       = 0;
r_def       = zeros(dim, 1);
rd_def      = zeros(dim, 1);
rdd_def     = zeros(dim, 1);
rddd_def    = zeros(dim, 1);
qk          = 0;
qd_k        = 0;
qdd_k       = 0;
feedrate    = 0;
maxConstantFeedrate = 0;
curvIndex   = int32( 0 );
zspdmode    = ZSpdMode.NN;

PStrct = struct('u',    u_def, ...
                'r',    r_def, ...
                'rd',   rd_def, ...
                'rdd',  rdd_def, ...
                'rddd', rddd_def, ...
                'qk',   qk, ...
                'qd_k', qd_k, ...
                'qdd_k',qdd_k, ...
                'feedrate', feedrate, ...
                'curvIndex', curvIndex, ...
                'zspdmode', zspdmode,...
                'maxConstantFeedrate', maxConstantFeedrate);
         
if ~coder.target('matlab')

MAX_SIZE_AXIS = 9;
coder.cstructname(PStrct, 'ProfileStrct');

coder.varsize('PStrct.r',       [MAX_SIZE_AXIS, 1], [1, 0]);
coder.varsize('PStrct.rd',      [MAX_SIZE_AXIS, 1], [1, 0]);
coder.varsize('PStrct.rdd',     [MAX_SIZE_AXIS, 1], [1, 0]);
coder.varsize('PStrct.rddd',    [MAX_SIZE_AXIS, 1], [1, 0]);
end

end