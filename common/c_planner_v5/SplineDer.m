function sp1D = SplineDer(sp)

p=sp.dim;
P=sp.coefs;

for i=1:size(P,2)-1
    
    coefsD(:,i) = (p/(sp.knots(i+p+1)-sp.knots(i+1))).*(P(:,i+1)-P(:,i));

end

sp1D.form='B-';
sp1D.knots=sp.knots(2:end-1);
sp1D.coefs=coefsD;
sp1D.number=sp.number-1;
sp1D.order=sp.order-1;
sp1D.dim=sp.dim;
