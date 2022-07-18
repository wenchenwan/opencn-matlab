
compress_end=ctx.q_compress.size();

L_all = zeros(1,compress_end);

for i=1:compress_end
    
    Curv = ctx.q_compress.get(i);
    
    if Curv.Info.Type==CurveType.Spline
        L_all(i)=LengthCurv(ctx, Curv, 0, 1);
    else
        L_all(i)=0;
    end
        
end

figure(2)
stem(L_all)
xlabel('smooth segm nr');
ylabel('segment length [mm]');
hold on