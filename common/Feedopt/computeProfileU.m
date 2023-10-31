function [ profileList ] = computeProfileU( Bl, Coeff )
[ BasisVal, BasisValD, BasisValDD ] = ...
    bspline_base_eval( Bl , Bl.breakpoints );

a = BasisValDD( 1 : end -1 , : ) * Coeff / 2;
b = BasisValD( 1 : end -1 , : )  * Coeff;
c = BasisVal( 1 : end -1 , : )   * Coeff;

NInterval   = length( Bl.breakpoints ) -1;
profile     = create_default_profile();
profileList = repmat( profile, NInterval, 1 );

Nt          = 10;
indVec      = 1 : ( Nt + 1 );
timeVec     = zeros( 1, ( Nt -1 ) * NInterval + 1 );

for j = 1 : NInterval
    profileList( j ).u0 = Bl.breakpoints( j );
    profileList( j ).u1 = Bl.breakpoints( j + 1 );
    if( j > 1 )
        profileList( j ).t0 = profileList( j-1 ).t1;
    else
        profileList( j ).t0 = 0;
    end

    profileList( j ).a = a( j );
    profileList( j ).b = b( j );
    profileList( j ).c = c( j );

    profileList( j ) = compute_profile_type( profileList( j ) );
    profileList( j ) = compute_switching_time( profileList( j ) );
    
    timeVec( indVec ) = linspace( profileList( j ).t0, profileList( j ).t1, Nt + 1 );
    indVec = indVec + Nt;
end

uVec    = zeros( size( timeVec ) );

for ind = 1 : length( timeVec )
    t           = timeVec( ind );
    uVec( ind ) = eval_profile( profileList, t );
end

end

function [ profile ] = compute_profile_type( profile )

if( profile.a  < 0 )
    profile.type = 4; % Sinusoidal
    return;
end

if( profile.a  > 0 )
    profile.type = 3; % Exponential
    return;
end

if( abs( profile.b ) > 0 )
    profile.type = 2; % Quadratic
    return;
end

if( abs( profile.c ) > 0 )
    profile.type = 1; % Linear
    return;
end

profile.type = 0; % Error
end

function [ u ] = eval_profile( profileList, time )

NInterval = length( profileList );

for j = 1 : NInterval
    if ( time >= profileList( j ).t0 && ...
         time <= profileList( j ).t1 )
        [ u ] = eval_profile_from_time( profileList( j ), time );
        break;
    end
end

end

function [ u ] = eval_profile_from_time( profile, time )

[ type, ~, ~, a, b, c, u0, u1 ] = get_field_profile( profile  );

dt = time - profile.t0;

switch type
    case 1  % Linear
        u = u0 + sqrt( c ) * dt;
    case 2  % Quadratic
        A = b / 4; B = sqrt( c ); C = u0;
        u = A * dt^2 + B * dt + C;
    case 3  % Exponantial        
        zs      = -b / ( 2 * a );
        kSquare = c - b^2 / ( 4 * a );
        aSqrt   = sqrt( a );
        xStar2  = aSqrt * ( -zs );
        t0      = eval_exponantial_time( xStar2, kSquare );
        Y       = exp( aSqrt * dt + t0 );
        X       = ( Y - kSquare / Y ) / 2;
        u       = X / aSqrt + u0 + zs;
        
        if( ~( u1 +1E-5 >= u ) )
            u       = -X / aSqrt + u0 + zs;
        end

    case 4  % Sinusoidal
        zs      = -b / ( 2 * a );
        kSquare = c - b^2 / ( 4 * a );
        ocn_assert( kSquare >= 0, "Profile : Case 4 : root on not positive value...", mfilename );
        aSqrt   = sqrt( abs( a ) );
        k       = sqrt( kSquare );
        t0      = asin( ( ( -aSqrt * zs ) / k ) );
        u       = k / aSqrt * sin( aSqrt * dt + t0 ) + u0 + zs;
    otherwise
        ocn_assert( 0, "Profile : Case 0...", mfilename );
end
    ocn_assert( u >= u0 -1E-5, "Profile : case " + type + " : u is smaller than u0...", mfilename );
    ocn_assert( u1 +1E-5 >= u, "Profile : case " + type + " : u is larger than u1...", mfilename );

end

function [ profile ] = compute_switching_time( profile  )
[ type, t0, t1, a, b, c, u0, u1 ] = get_field_profile( profile  );
switch type
    case 1  % Linear
        ocn_assert( c > 0, "Profile : Case 1 : c should be positive...", mfilename );
        t1 = ( u1 - u0 ) / sqrt( c );
    
    case 2  % Quadratic
        ocn_assert( c >= 0, "Profile : Case 2 : c should be positive...", mfilename );
        x   = u1 - u0;
        num = b * x + c;
        ocn_assert( num > 0, "Profile : Case 2 : root on not positive value...", mfilename );
        t1  = 2 * x / ( sqrt( c ) + sqrt( num ) );

    case 3  % Exponantial
        zs      = -b / ( 2 * a );
        kSquare = c - b^2 / ( 4 * a );
        aSqrt   = sqrt( a );
        xStar   = aSqrt * ( u1 - u0 -zs );
        num     = eval_exponantial_time( xStar, kSquare );
        xStar2  = aSqrt * ( -zs );
        num2    = eval_exponantial_time( xStar2, kSquare );
        t1      = ( num - num2 ) / aSqrt;

    case 4  % Sinusoidal
        zs      = -b / ( 2 * a );
        kSquare = c - b^2 / ( 4 * a );
        ocn_assert( kSquare >= 0, "Profile : Case 4 : root on not positive value...", mfilename );
        aSqrt   = sqrt( abs( a ) );
        k       = sqrt( kSquare );
        ocn_assert( k > 0, "Profile : Case 4 : den should be g.t. zero...", mfilename );
        x1      = aSqrt * ( u1 - u0 - zs );
        x0      = -aSqrt * zs;
        t1      = ( asin( x1 / k) - asin( x0 / k) ) / aSqrt;

    otherwise
        ocn_assert( 0, "Profile : Case 0...", mfilename );
end
ocn_assert( t1 >= 0, "Profile : case " + type + " : t1 is not g.t. than t0...", mfilename );

profile.t1 = t1 + t0;
end

function [ type, t0, t1, a, b, c, u0, u1 ] = get_field_profile( profile  )
type    = profile.type;
t0      = profile.t0;
t1      = profile.t1;
a       = profile.a;
b       = profile.b;
c       = profile.c;
u0      = profile.u0;
u1      = profile.u1;
end

function [ profile ] = create_default_profile()
profile = create_profile( 0, 0, 0, 0, 0, 0, 0, 0 );
end

function [ profile ] = create_profile( type, t0, t1, a, b, c, u0, u1 )
profile = struct( "type", type, "t0", t0, "t1", t1, "u0", u0, "u1", ...
    u1, "a", a, "b", b, "c", c );
end

function [ res ] = eval_exponantial_time( x, kSquare )

num = x^2 + kSquare;

ocn_assert( num >= 0, "Profile : Case 3 : root on not positive value...", mfilename );

if( x < 0 )
    num = -kSquare / ( x - sqrt( num ) );
else
    num = x + sqrt( num );
end

res = log( abs( num ) );

end