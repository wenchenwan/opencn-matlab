function [ctx, optimized, opt_struct] = FeedoptPlan(ctx)
global DebugActive
%#codegen
% See InitFeedoptPlan for information about the context variable ctx

c_assert(ctx.errcode == FeedoptPlanError.Success, 'FeedoptPlan: error code was not handled');


optimized = false;
end_flag = false;

% opt_struct = struct('Coeff', zeros(ctx.cfg.MaxNCoeff, 1),...
%     'CurvStruct', ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN));
% coder.cstructname(opt_struct, 'OptCurvStruct');

opt_struct = ConstrLineStruct([0,0,0]', [0,0,0]', 0.2, ZSpdMode.NN);

switch ctx.op
    case Fopt.Init
        ctx.op = Fopt.GCode;
        
%         coder.varsize('OptSegment', [1, FeedoptLimits.MaxNHorz], [0, 0]);
%         coder.varsize('Coeff', [FeedoptLimits.MaxNCoeff, FeedoptLimits.MaxNHorz], [1,1]);
        
        % fprintf('Starting optimization with NHorz = %d\n', ctx.cfg.NHorz);
%         
    case Fopt.GCode
        status = int32(ReadGCode(ReadGCodeCmd.Load, ctx.cfg.source));
        DebugLog('Reading G-code...\n');
        while status
            [status, CurvStruct] = ReadGCode(ReadGCodeCmd.Read, '');
            if status == 1 && CurvStruct.Type ~= 0
                ctx.q_gcode.push(CurvStruct);
            end
        end
        if ctx.q_gcode.isempty()
            ctx.op = Fopt.Finished;
            fprintf('ERROR: Optimization failed, Gcode queue is empty\n');
            return;
        end
        last = ctx.q_gcode.rget(1);
        if last.zspdmode == ZSpdMode.NN
            last.zspdmode = ZSpdMode.NZ;
        elseif last.zspdmode == ZSpdMode.ZN
            last.zspdmode = ZSpdMode.ZZ;
        end
        ctx.q_gcode.set(ctx.q_gcode.size, last);
        ctx.op = Fopt.Check;
    
    case Fopt.Check
        ctx = CheckCurvStructs(ctx);
        ctx.op = Fopt.Compress;

    case Fopt.Compress
        if ctx.cfg.SkipCompressing
            ctx = ExpandZeroStructs(ctx);
        else
            ctx = CompressCurvStructs(ctx);
        end
        ctx.op = Fopt.Smooth;
        
    case Fopt.Smooth
        ctx = SmoothCurvStructs(ctx);
        ctx.op = Fopt.Split;
            
    case Fopt.Split
        ctx = SplitCurvStructs(ctx);
        ctx.op = Fopt.Opt;
        
    case Fopt.Opt
        if ctx.q_split.isempty
            ctx.op = Fopt.Finished;
            return;
        end
        ctx.op = Fopt.Opt;
        
        if ctx.cfg.DebugOptimProgress
            fprintf('%4d/%u\n', ctx.k0, ctx.q_split.size);
        end
        
        if ctx.go_next
            ctx.k0 = ctx.k0 + 1;
            ctx.n_optimized = ctx.n_optimized + 1;
        end
        
        
        if ctx.n_optimized < ctx.q_split.size
            if ctx.try_push_again
                % Do nothing, we already have the last one optimized
            elseif ~ctx.reached_end
                OptSegment = repmat(ctx.q_split.get(1), 1, ctx.cfg.NHorz);
                
                first = ctx.q_split.get(ctx.k0);
                if first.zspdmode == ZSpdMode.ZN
                    opt_struct = first;
                    optimized = true;
                    [v_0, at_0] = CalcZeroStartConstraints(ctx, first, 1);
                    ctx.v_0 = v_0;
                    ctx.at_0 = at_0;
                    ctx.zero_start = true;
                    return;
                end
                
                k1temp = int32(ctx.k0 + ctx.cfg.NHorz - 1);
                if k1temp > ctx.q_split.size
                    ctx.reached_end = true;
                    k1 = int32(ctx.q_split.size);
                else
                    k1 = int32(k1temp);
                end
                
                ctx.at_1 = 0;
                ctx.v_1 = 0;
                
                nopt = 0;
                DebugLog('============= FEEDRATE PLANNING ================\n')
                kend = ctx.k0;
                for k = ctx.k0:k1
                    NextCurv = ctx.q_split.get(k);
                    if NextCurv.zspdmode == ZSpdMode.NZ
                        % If we reach an NZ segment, we set the final velocity
                        % and tangent acceleration constraints to the ones
                        % specified by the segment, and pretend this is the
                        % end of all segments
                        [v_0, at_0] = CalcZeroStartConstraints(ctx, NextCurv, 1);
                        ctx.at_1 = -at_0;
                        ctx.v_1 = v_0;
                        ctx.zero_end = true;
                        ctx.reached_end = true;
                        kend = k;
                        break;
                    elseif NextCurv.zspdmode == ZSpdMode.NN
                        nopt = nopt + 1;
                        OptSegment(nopt) = NextCurv;
                        
                        if DebugActive
                            PrintCurvStruct(ctx, OptSegment(k-ctx.k0+1))
                        end
                        if k < k1
                            DebugLog('-----------------------------------\n')
                        end
                    else
                        error('Wrong ZspdMode');
                    end
                end
                DebugLog('================================================\n')
                
                Retry = 0;
                success = false;
                Coeff = [];
                
                while Retry < 100 && ~success
                    [ctx, Coeff, ~, success] = FeedratePlanning_v4(ctx, OptSegment, ctx.cfg.amax, ctx.cfg.jmax,...
                        ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr,...
                        ctx.Bl, ctx.u_vec, min(ctx.cfg.NHorz, nopt));

                    if success == 0 && ctx.zero_start
                        fprintf('ZeroStart at k = %d failed, halving jerk\n', ctx.k0-1);
                        [v_0, at_0] = CalcZeroStartConstraints(ctx, ctx.q_split.get(ctx.k0 - 1), 0.5^Retry);
                        ctx.v_0 = v_0;
                        ctx.at_0 = at_0;
                    end
                    
                    if success == 0 && ctx.zero_end
                        fprintf('ZeroEnd at k = %d failed, halving jerk\n', kend);
                        [v_0, at_0] = CalcZeroStartConstraints(ctx, ctx.q_split.get(kend), 0.5^Retry);
                        ctx.at_1 = -at_0;
                        ctx.v_1 = v_0;
                    end
                    
                    Retry = Retry + 1;
                end
                
                if coder.target('matlab')
                    assert(success == 1);
                end
                
                ctx.zero_start = false;
                ctx.zero_end = false;
                
                ctx.Coeff = Coeff;
                if success == 0
                    for nprint = 1:ctx.cfg.NHorz
                        if DebugActive
                            PrintCurvStruct(ctx, OptSegment(1));
                        end
                    end
                    if coder.target('MATLAB')
                        error('OPTIMIZATION FAILED')
                    else
                        fprintf('OPTIMIZATION FAILED!\n');
                        ctx.errcode = FeedoptPlanError.OptimizationFailed;
                    end
                    ctx.op = Fopt.Finished;
                    return;
                end
            else
                % If we have reached the end of the optimizing segment, we
                % can just copy out the coefficients for the whole horizon
                ctx.Coeff(:, 1:end-1) = ctx.Coeff(:, 2:end);
            end
           
            optimized = true;
            opt_struct = ctx.q_split.get(ctx.n_optimized + 1);
            opt_struct.Coeff = ctx.Coeff(:, 1);
            
            if opt_struct.zspdmode == ZSpdMode.NZ
                ctx.reached_end = false;
            end
            
        else
            ctx.op = Fopt.Finished;
        end
        
    case Fopt.Finished
        ctx.op = Fopt.Finished;
        
    otherwise
        fprintf('FEEDOPT: WRONG STATE\n')
        ctx.op = Fopt.Finished;
        
end

end
