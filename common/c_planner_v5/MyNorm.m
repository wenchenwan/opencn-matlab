function n = MyNorm(x)
coder.inline('always');
n = sqrt(sum(x.^2));
end

