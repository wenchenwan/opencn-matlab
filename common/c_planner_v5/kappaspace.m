function uvec = kappaspace(ctx, CurvStruct)
BaseStep = 1/sqrt(LengthCurv(ctx, CurvStruct, 0, 1))/10;

u = 0;
uvec = zeros(1,1000);

for k = 1:length(uvec)
    uvec(k) = u;
    [~, r1D, r2D, ~] = EvalCurvStruct(ctx, CurvStruct, u);
    % N: normal acceleration, v: velocity, R: radius
    % N = v^2/R
    % R = v^2/N
    N = norm(cross(r1D/norm(r1D), r2D));
    v = norm(r2D);
    R = v.^2/N;
    K = 1/R;
    
    Step = min(BaseStep, BaseStep/K);
    u = u + Step;
    if u > 1
        uvec(k+1) = 1;
        k = k + 1;
        break;
    end
end

uvec = uvec(1:k);

end