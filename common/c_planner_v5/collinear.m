function value = collinear(u, v, angle_d)
    if (norm(u) < eps || norm(v) < eps)
        value = true;
        return;
    end
    value = dot(u,v)/(norm(u)*norm(v)) > cosd(angle_d);
end