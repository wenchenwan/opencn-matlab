function [C, success, status, msg] = c_simplex(f, A, b, Aeq, beq, ctx)
msg = "";
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
        coder.rref(b), bsize, coder.rref(beq),beqsize,...
        coder.ref(C), Csize);
    %         C = solution.solution;
    success = status == 0;
    % Status : 
    %       0 : Primal Dual Optimality 
    %       1 : Primal Infeasible
    %       2 : Dual Infeasible
    %       3 : Max iteration reached
    %       4 : isAbandoned
    c_prof_out(mfilename);
else
    %         options = optimoptions('linprog', 'OptimalityTolerance', 1e-6, ...
    %                        'ConstraintTolerance', 1e-6, 'Display', 'iter');
    %         [C, ~, exitflag, output] = linprog(f, A, b, Aeq, beq, zeros(numel(f),1), [], options);
    %         success = exitflag == 1;
    %         if ~success
    %             fprintf('linprog failed with exitflag = %d\n', exitflag);
    %         end
    if ( ~ctx.cfg.opt.USE_LINPROG )
        [C0, success, status] = c_simplex_mex(f, A, b, Aeq, beq );
        msg = printOptStatus( status );
        
        if(~success && ctx.cfg.opt.EnableFindReasonInfeasibility)
            msg = msg + findReasonInfeasibility(f, A, b, Aeq, beq); 
        end
        
        C = C0(1:numel(f));
    else
        options = optimoptions('linprog', ...
            'Algorithm', 'dual-simplex', ... % dual-simplex, interior-point
            'OptimalityTolerance', 1e-6, ...
            'ConstraintTolerance', 1e-6, ...
            'Display', 'none');
        [C, ~, exitflag] = linprog(f, A, b, Aeq, beq, zeros(numel(f),1), [], options);
%                     [C, ~, exitflag] = linprog(f, A, b, Aeq, beq, zeros(numel(f),1), [], options);
        success = exitflag == 1;
        status = exitflag;
    end
   
end
end

function [statusMsg] = printOptStatus( status )
    %printOptStatus : Print the optimization status
    % 
    % ctx       : the context
    % retry     : the number of iteration
    % status    : the status of the optimization
   
    statusMsg = "";
    if( status == 0), return; end % Success

    switch status
        case 1
            statusMsg = statusMsg + " 1 - Primal infeasibility";
        case 2
            statusMsg = statusMsg + " 2 - Dual infeasibility";
        case 3
            statusMsg = statusMsg + " 3 - Maximum iterations reached";
        case 4
            statusMsg = statusMsg + " 4 - Optimization has abandoned";
        otherwise
            statusMsg = statusMsg + " " + status + " - Status unknwon";
    end

    statusMsg = "\t Error: Optimization failed | \t Status : "  ...
                + statusMsg + " |\n";
%    diary on;
%    DebugLog(DebugCfg.Validate, ...
%         "\t Error: Optimization failed | \t Status : "  + statusMsg + " |");
%    diary off;
end

function [msg] = findReasonInfeasibility(f, A, b, Aeq, beq)
    % findReasonInfeasibility : Try to find a reason to the infeasibility
    %       1 - Check if the constraints are feasible
    %       2 - Check if the inequality constraints are feasible
    %       3 - Check if the equality constraints are feasible
    %       4 - Check which equality constraints is not feasible
    fTest = f; ATest = A; AeqTest = Aeq; bTest = b; beqTest = beq; 
    msg = "\t\t";
    
    % 1.
    fTest(:) = 0; [~, success] = c_simplex_mex(fTest, A, b, Aeq, beq);
    if (success)
        msg = msg + "Constraints are feasible w.r.t. the constraints but" + ...
            " fails due to the objectif \n"; return; 
    else
        msg = msg + "1. Constraints are not feasible\n";
    end

    % 2.
    AeqTest = zeros(1, size(AeqTest,2)); beqTest = 0;
    [~, successInEq] = c_simplex_mex(fTest, A, b, AeqTest, beqTest);
    msg = msg + "\t\t2. Inequality constraints (only) are ";
    if (~successInEq), msg = msg +  "not "; end; msg = msg + "feasible\n";
    
    % 3. 
    ATest(:) = 0; bTest(:) = 0; AeqTest = Aeq; beqTest = beq;
    [~, successEq] = c_simplex_mex(fTest, ATest, bTest, AeqTest, beqTest);
    msg = msg + "\t\t3. Equality constraints (only) are ";
    if (~successEq), msg = msg +  "not "; end; msg = msg + "feasible\n";

    % 4.
    if( successEq && successInEq )
        successVec = zeros(1, length(beq));
        indVel = 1:2:length(beq);
        indAcc = 2:2:length(beq);

        for j = 1 : length(beq)
            [~, successVec(j)] = c_simplex_mex(fTest, A, b, AeqTest(j,:), beqTest(j));
%             [~, ~, successVec(j)] = linprog(fTest, A, b, AeqTest(j,:), beqTest(j));

        end
        msg4 = "\t\t" + "4. Inequality constraints with the continuity " + ...
            "constraints are infeasible for : \n";
        if(any(successVec(indVel) == 0)), msg = msg + msg4 + ...
                "\t\t\t - velocity(ies) : " + ...
                num2str( ( indVel( successVec(indVel) == 0 ) + 1 ) / 2) + ...
                " (last : " + length(beq) / 2 + ")\n"; 
        end
        
        if(any(successVec(indAcc) == 0)), msg = msg + msg4 + ...
                "\t\t\t - acceleration(s) : " + ...
                num2str( indAcc( successVec(indAcc) == 0 ) / 2) + ...
                " (last : " + length(beq) / 2+ ")\n"; 
        end
    end

end