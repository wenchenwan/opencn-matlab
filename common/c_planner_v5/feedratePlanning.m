function [ ctx, optimized, opt_struct, quit ] = feedratePlanning( ctx )
% Work still in progress Hugo ( 27.04.22 )
trafo = false; % TRAFO flag disable
HSC = false;
Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0;

opt_struct = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
    Doff, [0,0,0]', [0,0,0]', A0, A1, U0, ...
    U1, 0.2, ZSpdMode.NN);

quit        = false;
optimized   = false;

if ctx.q_split.isempty
    if coder.target('matlab')
        diary on;
    end
    DebugLog(DebugCfg.Validate, 'Queue empty...\n');
    ctx.op = Fopt.Finished;
    quit = true;
    return;
end
ctx.op = Fopt.Opt;

if IsEnabledDebugLog(DebugCfg.OptimProgress)
    fprintf('%4d/%u\n', ctx.k0, ctx.q_split.size);
end

% Increment index on q_split
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
            [v_0, at_0] = calcZeroStartConstraints(ctx, first);
            ctx.v_0 = v_0;
            ctx.at_0 = at_0;
            ctx.zero_start = true;
            quit = true;
            return;
        end

        % Get final index for the sliding horizon
        k1temp = int32(ctx.k0 + ctx.cfg.NHorz - 1);
        if k1temp > ctx.q_split.size
            ctx.reached_end = true;
            k1 = int32(ctx.q_split.size);
        else
            k1 = int32(k1temp);
        end

        nopt = 0;
        DebugLog(DebugCfg.Global, 'FEEDRATE PLANNING...\n')
        kend = ctx.k0;
        for k = ctx.k0:k1
            NextCurv = ctx.q_split.get(k);
            if NextCurv.zspdmode == ZSpdMode.NZ
                % If we reach an NZ segment, we set the final velocity
                % and tangent acceleration constraints to the ones
                % specified by the segment, and pretend this is the
                % end of all segments
                [v_0, at_0] = calcZeroStartConstraints(ctx, NextCurv);
                ctx.at_1 = -at_0;
                ctx.v_1 = v_0;
                ctx.zero_end = true;
                ctx.reached_end = true;
                kend = k;
                break;
            elseif NextCurv.zspdmode == ZSpdMode.NN
                nopt = nopt + 1;
                OptSegment(nopt) = NextCurv;

                if IsEnabledDebugLog(DebugCfg.Global)
                    PrintCurvStruct(ctx, OptSegment(k-ctx.k0+1))
                end
                if k < k1
                    DebugLog(DebugCfg.Global, ...
                        '-----------------------------------\n')
                end
            else
                error('Wrong ZspdMode');
            end
        end
        DebugLog(DebugCfg.Global, ...
            '================================================\n')

        Retry = 0;
        success = false;
        Coeff = [];
        ctx.at_1 = ctx.cfg.at_1; ctx.v_1 = ctx.cfg.v_0;
        MAX_RETRY = 100;
        while Retry < MAX_RETRY && ~success

            if ctx.zero_start
                [v_0, at_0] = calcZeroStartConstraints( ctx, ctx.q_split.get( ctx.k0 - 1 ) );
                ctx.v_0 = v_0;
                ctx.at_0 = at_0;
            end

            if ctx.zero_end
                [v_0, at_0] = calcZeroStartConstraints( ctx, ctx.q_split.get( kend ) );
                ctx.at_1 = -at_0;
                ctx.v_1 = v_0;
            end

            [ctx, Coeff, ~, success, status, msg] = FeedratePlanning(ctx, OptSegment, ctx.cfg.amax, ctx.cfg.jmax,...
                ctx.BasisVal, ctx.BasisValD, ctx.BasisValDD, ctx.BasisIntegr,...
                ctx.Bl, ctx.u_vec, min(ctx.cfg.NHorz, nopt));
            if( ~success )
                Retry = Retry + 1;
                if coder.target('matlab')
                    diary on;
                    DebugLog(DebugCfg.Validate, " k : " + ctx.k0 + " \t | retry : " + Retry + "\n");
                    DebugLog(DebugCfg.Validate, msg);
                    diary off;
                    ctx.at_1 = [];
                    Retry = MAX_RETRY;
                end

                if( ctx.zero_start )
                    DebugLog(DebugCfg.Warning, 'ZeroStart at k = %d failed, halving jerk\n', ctx.k0-1);
                end

                if( ctx.zero_end )
                    DebugLog(DebugCfg.Warning, 'ZeroEnd at k = %d failed, halving jerk\n', kend);
                end
            end
        end

        if coder.target('matlab')
            c_assert(success == 1,'Feedopt not successfull after 100 retrys!');
        end

        ctx.zero_start = false;
        ctx.zero_end = false;

        ctx.Coeff = Coeff;
        if success == 0
            for nprint = 1:ctx.cfg.NHorz
                if IsEnabledDebugLog(DebugCfg.Global)
                    PrintCurvStruct(ctx, OptSegment(1));
                end
            end
            if coder.target('MATLAB')
                c_assert('OPTIMIZATION FAILED');
            else
                DebugLog(DebugCfg.Global, 'OPTIMIZATION FAILED!\n');
                ctx.errcode = FeedoptPlanError.OptimizationFailed;
            end
            ctx.op = Fopt.Finished;
            quit = true;
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
end