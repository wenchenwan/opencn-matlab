function value = iscusp(u, v, angle_d)
    value = dot(u,v)/(norm(u)*norm(v)) < cosd(180 - angle_d);
end
