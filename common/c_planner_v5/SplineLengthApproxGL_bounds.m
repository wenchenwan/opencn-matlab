function L  = SplineLengthApproxGL_bounds(ctx, Curv, u1, u2)
% computes approximately the arc length L with arbitrary integration bounds u1 and u2.
% The computation is based on numerical Gauss Legendre integration.
% This function takes usage of the precalculated arc lengths between knots.
%
% get the sp structure
Spline = ctx.q_splines.get( Curv.sp_index );
sp     = Spline.sp;
Knots  = sp.knots( 4 : end-3 );  % eliminate multiplicities at the end points
Lk     = sp.Lk;
%
c_assert(u2 > u1,          'u2 must be greater than u1');
c_assert(u1 >= Knots(1),   'u1 must be greater or equal than the first spline knot');
c_assert(u2 <= Knots(end), 'u2 must be smaller or equal than the last spline knot');
%
k = 1;
%
while u1 > Knots(k)
    k = k + 1;
end
%
if u2 < Knots(k)
    L = SplineLengthApprox_Interval1(ctx, Curv, u1, u2);       % u1 and u2 in the same break interval
else
    L = SplineLengthApprox_Interval1(ctx, Curv, u1, Knots(k)); % remaining length to next break point
    while u2 > Knots(k)
        L = L + Lk(k);  % sum up precalculated length between knots
        k = k + 1;
    end
    L = L + SplineLengthApprox_Interval1(ctx, Curv, Knots(k), u2); % remaining length to u2
end
    
