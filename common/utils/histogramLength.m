function histogramLength( ctx, queue, name )

N = queue.size();

L = zeros( N ,1 );
for j = 1 : N
    L( j ) = LengthCurv( ctx, queue.get( j ), 0, 1 );
end

disp( name );
disp( "Min : "      + min( L ) );
disp( "Max : "      + max( L ) );
disp( "Number : "   + N );

Llog = log10( L );

figure();
histogram( Llog ); title( name ); 
% set( gca, 'yscale','log' )

xlabel( "Length log10( [mm] )");
ylabel( "Bin counts");

% pause();
end