function S = c_matrix(M) %#codegen
    S.data_ = M;
    S.M_ = size(M, 1);
    S.N_ = size(M, 2);
    
    coder.varsize('S._Data');
    coder.cstructname(S, 'Matrix', 'extern');
end
