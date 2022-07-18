function value = collinear(u, v, tol_cos)
    if (norm(u) < eps || norm(v) < eps)
        value = true;
        return;
    end
    cos_angle = dot(u,v)/(MyNorm(u)*MyNorm(v));
    value = cos_angle >= tol_cos;
end
