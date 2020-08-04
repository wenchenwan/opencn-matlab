
u_vec=[1,3,7,9];
u=[];

for k=1:length(u_vec)-1
    
    if  ~isempty(u)
        u=u(1:end-1);
    end
    
    u=[u linspace(u_vec(k), u_vec(k+1), 10)];
    
end