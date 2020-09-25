function [value, real_angle_d] = collinear(u, v, tol_angle_d)
    if (norm(u) < eps || norm(v) < eps)
        value = true;
        real_angle_d = 0;
        return;
    end
    real_angle_d = acosd( dot(u,v)/(norm(u)*norm(v)) );
    value = cosd(real_angle_d) > cosd(tol_angle_d);
end