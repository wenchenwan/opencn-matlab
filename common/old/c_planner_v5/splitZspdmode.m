function [splittedCurv] = splitZspdmode( initCurv, splittedCurv, u0, u1, Bound0, Bound1)
% splitZspdmode
% 
% Assigns correctly the zspdmode for each splitted curvStruct
%
% INPUT :
% initCurv
% u0
% u1
% Bound0
% Bound1
%
% OUTPUT :
% splittedCurv
%

% zspdmode : ZN => [ZN, NN, ..., NN]
if ( initCurv.Info.zspdmode == ZSpdMode.ZN )
    splittedCurv.Info.zspdmode = ZSpdMode.NN;
    if u0 == Bound0
        splittedCurv.Info.zspdmode = ZSpdMode.ZN;
    end
% zspdmode : NZ => [NN, ..., NN, NZ]
elseif ( initCurv.Info.zspdmode == ZSpdMode.NZ )
    splittedCurv.Info.zspdmode = ZSpdMode.NN;
    if u1 == Bound1
        splittedCurv.Info.zspdmode = ZSpdMode.NZ;
    end
% zspdmode : ZZ => [ZN, NN, ..., NN, NZ]
elseif ( initCurv.Info.zspdmode == ZSpdMode.ZZ )
    splittedCurv.Info.zspdmode = ZSpdMode.NN;
    if u0 == Bound0
        splittedCurv.Info.zspdmode = ZSpdMode.ZN;
    elseif u1 == Bound1
        splittedCurv.Info.zspdmode = ZSpdMode.NZ;
    end
end

end