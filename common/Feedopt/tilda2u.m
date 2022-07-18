function [ u, ud, udd, uddd ] = tilda2u( u, ud, udd, uddd, a, b ) 
% Input : 
%   u          :  [ N x M ]
%   ud         :  [ N x M ]
%   udd        :  [ N x M ]
%   uddd       :  [ N x M ]
% Outputs : 
%   u          :  [ N x M ]
%   ud         :  [ N x M ]
%   udd        :  [ N x M ]
%   uddd       :  [ N x M ]

if( ~ isempty( u ) )
    u  = ( u - b ) / a;
else
    u  = 0;
end

if( ~ isempty( ud ) )
    ud = ud / a;
else
    ud = 0;
end

if( ~ isempty( udd ) )
    udd = udd / a;
else
    udd = 0;
end

if( ~ isempty( uddd ) )
    uddd = uddd / a;
else
    uddd = 0;
end

end