function [C, success, status] = c_simplex(f, A, b, Aeq, beq)
if coder.target('rtw') || coder.target('mex')
    c_prof_in(mfilename);
    c_prof_in('join_A');
    Atot = [A; Aeq];
    c_prof_out('join_A');
%     MaxCoeff = FeedoptLimits.MaxNCoeff*FeedoptLimits.MaxNHorz;
    [NCoeff, NHorz] = size(f);
    C = zeros(NCoeff, NHorz);
    coder.varsize('C', [Inf, Inf], [1,1]);
    
    [Aisd, Ajsd, Avs] = find(Atot);
    Ais = int32(Aisd)-1;
    Ajs = int32(Ajsd)-1;

    coder.varsize('Avs', [Inf, 1], [1, 0]);
    coder.varsize('Ais', [Inf, 1], [1, 0]);
    coder.varsize('Ajs', [Inf, 1], [1, 0]);
    
    fsize = int32(size(f));
    Asize = int32(size(Atot));
    An = int32(nnz(Avs));
    bsize = int32(size(b));
    beqsize = int32(size(beq));
    Csize = int32(size(C));
    success = int32(0);
    status = int32(0);
    coder.updateBuildInfo('addSourceFiles','cpp_simplex.cpp', '$(START_DIR)/src/');
    coder.updateBuildInfo('addLinkFlags', LibInfo.clp.lflags);
    coder.cinclude('cpp_simplex.hpp');
    status = coder.ceval('simplex_solve', coder.rref(f), fsize,...
        coder.rref(Avs), coder.rref(Ais), coder.rref(Ajs), Asize, An,...
        coder.ref(b), bsize, coder.rref(beq),beqsize,...
        coder.ref(C), Csize);
    %         C = solution.solution;
    success = status == 0;
    c_prof_out(mfilename);
else
    %         options = optimoptions('linprog', 'OptimalityTolerance', 1e-6, ...
    %                        'ConstraintTolerance', 1e-6, 'Display', 'iter');
    %         [C, ~, exitflag, output] = linprog(f, A, b, Aeq, beq, zeros(numel(f),1), [], options);
    %         success = exitflag == 1;
    %         if ~success
    %             fprintf('linprog failed with exitflag = %d\n', exitflag);
    %         end
    if (true)
        [C0, success, status] = c_simplex_mex(f, A, b, Aeq, beq);
        C = C0(1:numel(f));
    else
        options = optimoptions('linprog', ...
            'Algorithm', 'dual-simplex', ... % dual-simplex, interior-point
            'OptimalityTolerance', 1e-6, ...
            'ConstraintTolerance', 1e-6, ...
            'Display', 'none');
                    [C, ~, exitflag] = linprog(f, A, b, Aeq, beq, zeros(numel(f),1), [], options);
        success = exitflag == 1;
        status = exitflag;
    end
   
end
end
