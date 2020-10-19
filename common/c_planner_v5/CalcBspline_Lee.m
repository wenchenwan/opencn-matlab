function sp3D = CalcBspline_Lee(cfg, points)
% if coder.target('rtw') || coder.target('mex')
    sp3D = CalcBspline_Lee_coder(cfg, points);
% else
%     sp3D = CalcBspline_Lee_matlab(points);
% end
end