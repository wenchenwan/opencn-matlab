X = zeros(20,20);
Y = X;
%addpath('c_planner')

% degree, nbreaks, samples
nbreak = 10;
deg = 3;
warning('off','MATLAB:mex:GccVersion');
% mex mex/bspline_create/bspline_create_mex.c ../src/c_spline.c -lgsl -lgslcblas -I../src
% mex mex/bspline_destroy/bspline_destroy_mex.c ../src/c_spline.c -lgsl -lgslcblas -I../src
% mex mex/bspline_eval/bspline_eval_mex.c ../src/c_spline.c -lgsl -lgslcblas -I../src
% mex mex/bspline_base_eval/bspline_base_eval_mex.c ../src/c_spline.c -lgsl -lgslcblas -I../src
% mex -I/usr/include/coin -lClp -lCoinUtils -largeArrayDims mex/simplex/simplex_mex.cpp...
%     ../src/cpp_simplex.cpp -I../src -I../gen_matlab
% 
Bl = bspline_create_mex(0, 1, deg, nbreak);

c = rand(Bl.n, 1);


x = linspace(0,1,100);
y = zeros(100,1);
for k = 1:100
    [yk, ykd, ykdd] = bspline_eval_mex(Bl, c, x(k));
    y(k) = yk;
end

[BasisVal, BasisValD,BasisValDD,BasisIntegr] = bspline_base_eval_mex(Bl, x); 

bspline_destroy_mex(Bl);
