function [ XSet ] = newtonRaphsonOnSet( f, df, XSet )
FXSet = XSet;
count = 0;
iterMax = 10;
tol = 1E-3;

while( count < iterMax && abs( diff( XSet ) ) > tol )
    count = count + 1;
    m = sum( XSet( [ 1, end ] ), 2 ) / 2;
    F = f( m );

    u = linspace( XSet( 1 ), XSet( end ), 100 );
    DF  = df( u );
    DFSet = [ min(DF), max(DF) ];

    for j = 1 : 2
        if( DFSet(j) ~= 0 )
        FXSet( j ) = m - F / DFSet( j );
        else
        FXSet( j ) = XSet( j );
        end
    end
    
    if( FXSet( 1 ) > FXSet( 2 ) )
        FXSet = flip( FXSet ); 
    end
  
    XSet( 1 ) = max( XSet(1), FXSet(1) );
    XSet( 2 ) = min( XSet(2), FXSet(2) );
    disp( "count : " + count + " XSet : " +  mat2str( XSet ) );
end

end