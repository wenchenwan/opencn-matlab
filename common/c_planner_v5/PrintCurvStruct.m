function PrintCurvStruct(ctx, S)

fprintf('--------- CURVE STRUCT ---------\n')
fprintf('%10s: %s\n', 'Type', CurveTypeToStr(S.Type));

switch S.Type
    case CurveType.Line
        
    case CurveType.Helix
        fprintf('%10s: [%.3f %.3f %.3f]\n', 'evec', S.evec(1), S.evec(2), S.evec(3))
        fprintf('%10s: %.3f\n', 'theta', S.theta);
        fprintf('%10s: %.3f\n', 'pitch', S.pitch);
    case CurveType.TransP5
        fprintf(' CoeffP5: \n');
        fprintf('| ')
        for CoeffRow = S.CoeffP5'
            for v = CoeffRow
                fprintf('%.3f ', v(1))
            end
            fprintf('| ')
        end
        fprintf('\n')
        fprintf('FeedRate: %.2f\n', S.FeedRate)
    case CurveType.Spline
    otherwise
        fprintf('!!! Type = %d, UNKNOWN !!!\n', int32(S.Type))
end
P0 = EvalCurvStruct(ctx, S, 0);
P1 = EvalCurvStruct(ctx, S, 1);
fprintf('%10s: [%.4f %.4f %.4f] -> [%.4f %.4f %.4f]\n',...
    'P', P0(1), P0(2), P0(3), P1(1), P1(2), P1(3))
fprintf('%10s: %e\n', 'Length', LengthCurv(ctx, S, 0, 1));
fprintf('ZSpdMode: %s\n', PrintZSpdMode(S.zspdmode))
fprintf('FeedRate: %.2f\n', S.FeedRate)
if S.UseConstJerk
    [v_0, at_0] = calcZeroStartConstraints( ctx, S );
    fprintf('ConstJerk: %e\n', S.ConstJerk)
    fprintf('v_0      : %f\n', v_0)
    fprintf('at_0     : %f\n', at_0)
end
end

function str = PrintZSpdMode(m)
switch m
    case ZSpdMode.NN
        str = "NN";
    case ZSpdMode.ZN
        str = "ZN";
    case ZSpdMode.NZ
        str = "NZ";
    case ZSpdMode.ZZ
        str = "ZZ";
    otherwise
        str = "<UNKNOWN>";
end
end

function str = CurveTypeToStr(Type)
switch Type
    case CurveType.Line
        str = 'Line';
    case CurveType.Helix
        str = 'Helix';
    case CurveType.TransP5
        str = 'TransP5';
    case CurveType.Spline
        str = 'Spline';
    otherwise
        str = '<UNKNOWN>';
end
end
