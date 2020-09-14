function n = MyNorm(x)
coder.inline('always');
n = mysqrt(sum(x.^2));
end

