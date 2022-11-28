clear; clc;
check_wkdir();

% We need first to choose what we whant to MEX.
% Several options are possible.
GenerateAll = false;

if( ~GenerateAll )
    GenerateDebug               = false;
    GenerateType                = false;
    GenerateResampling          = true;
    GenerateGCodeInterpreter    = false;
    GenerateQueues              = false;
    GenerateSimplex             = false;
    GenerateSpline              = false;
    GenerateKinematic           = false;
    GenerateTridiagonalSolver   = false;
%     GenerateFeedoptPlanRun      = false; % Does not work now
end
cfg = generate_mex_config();

% Some entry-point functions (memebers of codegen functions list)
% take output of the functions hereafter, as arguments.
% 'FeedoptDefaultConfig' and 'InitFeedoptPlan' must be entry-points functions, as well.
fcfg    = coder.OutputType('FeedoptDefaultConfig');
fctx    = coder.OutputType('initFeedoptPlan');
C       = coder.OutputType('constrCurvStructType');

global DebugActive sqrt_calls sin_calls cos_calls cot_calls DebugConfig
DebugActive = false;
sqrt_calls = 0;  
sin_calls = 0;
cos_calls = 0;
cot_calls = 0;
DebugConfig = 0;

% An object of this type is an argument to entry-points functions.
% C++ corresponding generated functions will accept
% a fixed-size (3) 1-dimentional array of doubles.
P0 = [0,0,0]';
trafo = false;
HSC = false;
Doff = 0.0;

% Include folders to add to the include path
% when compiling the generated C++ code.
cfg.CustomInclude = [...
    '../../ '...
    '. '...
    'src '...
    '../../rs274ngc '...
    '../../common/include '];

% Final codegen calls, according to what we
% have chosen to MEX (see top of this script).
% Output MEX files will have '_mex' filename postfix.

% We then be able to call them from our MATLAB code.

% Coder configuration 'coder.target('MATLAB')' must be true,
% when executing MEX files.

% Remove gen from path
ERROR_COLOR = 2;

if( ~GenerateAll && GenerateDebug )
    name = "Debug functions : ";
    disp(name + "start" );
    try
        DebugRep = 'gen_mex/debug';
        path_mex = genpath( DebugRep );

%         curve = coder.OutputType('constrCurvStructType');

        codegen('-config', cfg,'-d', DebugRep , ...
            'constrCurvStructType',...
            'FeedoptDefaultConfig',...
            'initFeedoptPlan', '-args', fcfg,...
            'buildConstr', '-args', {fctx, coder.typeof([constrCurvStructType], [1, Inf], [0,1]), ...
            coder.typeof(zeros(1,3) , [1, Inf], [0,1]),0.0,0.0,0.0,0.0, ...
            coder.typeof(zeros(1,1) , [Inf, Inf], [1,1]), ...
            coder.typeof(zeros(1,1) , [Inf, Inf], [1,1]), ...
            coder.typeof(zeros(1,1) , [1, Inf], [0,1])} ,...
            '-o', 'debug_mex' );
        disp(name + "success" );
        delete( 'debug_mex.mexa64' );
        addpath( path_mex );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n" );
    end
end

if( GenerateAll || GenerateType )
    name = "Mexing Types : ";
    disp(name + "start" );
    try
        TypeRep = 'gen_mex/types';
        path_mex = genpath( TypeRep );
        rmpath( path_mex );
        codegen('-config', cfg,'-d', TypeRep, ...
            'constrGcodeInfoStructType',...
            'constrGcodeInfoStruct', '-args', paramsDefaultGCodeInfo( StructTypeName.MEX ),...
            'constrBaseSplineType',...
            'constrBaseSpline', '-args', paramsDefaultBaseSpline( StructTypeName.MEX ),...
            'constrSplineType',...
            'constrSpline', '-args', paramsDefaultSpline( StructTypeName.MEX ),...
            'constrCurvStructType',...
            'constrCurvStruct', '-args', paramsDefaultCurv( StructTypeName.MEX ),...
            'constrHelixStruct', '-args', paramsDefaultHelix( StructTypeName.MEX ),...
            'constrHelixStructFromArcFeed', '-args', paramsDefaultHelixFromArcFeed( StructTypeName.MEX ), ...
            'constrLineStruct', '-args', paramsDefaultLine( StructTypeName.MEX ), ...
            'constrTransP5Struct', '-args', paramsDefaultTransition( StructTypeName.MEX ),...
            '-o', 'Type_mex');
        disp(name + "success" );
        delete( 'Type_mex.mexa64' );
        addpath( path_mex );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
    end
end

if( GenerateAll || GenerateQueues )
    name = "Mexing queues : ";
    disp(name + "start" );
    try
        QueueRep = 'gen_mex/queue';
        path_mex = genpath( QueueRep );
        rmpath( path_mex );
        mex mex/queue/queue_new.cpp     -output queue_new_mex    -outdir gen_mex/queue
        mex mex/queue/queue_delete.cpp  -output queue_delete_mex -outdir gen_mex/queue
        mex mex/queue/queue_push.cpp    -output queue_push_mex   -outdir gen_mex/queue
        mex mex/queue/queue_get.cpp     -output queue_get_mex    -outdir gen_mex/queue
        mex mex/queue/queue_set.cpp     -output queue_set_mex    -outdir gen_mex/queue
        mex mex/queue/queue_pop.cpp     -output queue_pop_mex    -outdir gen_mex/queue
        mex mex/queue/queue_size.cpp    -output queue_size_mex   -outdir gen_mex/queue
        mex mex/queue/queue_get_all.cpp -output queue_get_all_mex -outdir gen_mex/queue

        disp(name + "success" );
        addpath( path_mex );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
    end
end

if( GenerateAll || GenerateSpline )
    name = "Mexing bspline_create : ";
    disp(name + "start" );
    try
        splineRep = "gen_mex/spline/";
        path_mex = genpath( splineRep );
        rmpath( path_mex );

        fcfg = FeedoptDefaultConfig;
        codegen('-config', cfg,'-d', splineRep + "/bspline_create",...
            'bspline_create', '-args',...
            {fcfg.SplineDegree, coder.typeof(0.0, [1, Inf], [0, 1])},...
            '-o', 'bspline_create_mex');
        %fcfg.SplineDegree, linspace(0, 1, fcfg.NBreak)
        BlType = coder.OutputType('bspline_create');
        %
        fprintf('Mexing bspline_destroy\n')
        codegen('-config', cfg,'-d', splineRep + "/bspline_destroy",...
            'bspline_destroy', '-args', BlType,....
            'bspline_create', '-args', {fcfg.SplineDegree, coder.typeof(0.0, [1, Inf], [0, 1])},...
            '-o', 'bspline_destroy_mex');

        fprintf('Mexing bspline_base_eval\n')
        codegen('-config', cfg,'-d', splineRep + "/bspline_base_eval",...
            'bspline_base_eval', '-args', {BlType, coder.typeof(0.0,[1,Inf])},...
            'bspline_create', '-args', {fcfg.SplineDegree, coder.typeof(0.0, [1, Inf], [0, 1])},...
            '-o', 'bspline_base_eval_mex');

        fprintf('Mexing bspline_eval\n')
        codegen('-config', cfg,'-d', splineRep + "/bspline_eval",...
            'bspline_eval', '-args',...
            {BlType, coder.typeof(0.0, [1, Inf], [1, 0]), 0.5},...
            'bspline_create', '-args', {fcfg.SplineDegree, coder.typeof(0.0, [1, Inf], [0, 1])},...
            '-o', 'bspline_eval_mex');

        fprintf('Mexing bspline_eval_lee\n')
        codegen('-config', cfg,'-d', splineRep + "/bspline_eval_lee",...
            'bspline_eval_lee', '-args', {BlType, int32(0), coder.typeof(0.0,[1,Inf])},...
            'bspline_create', '-args', {fcfg.SplineDegree, coder.typeof(0.0, [1, Inf], [0, 1])},...
            '-o', 'bspline_eval_lee_mex');

        disp(name + "success" );

        delete( 'bspline_create_mex.mexa64' );
        delete( 'bspline_destroy_mex.mexa64' );
        delete( 'bspline_base_eval_mex.mexa64' );
        delete( 'bspline_eval_mex.mexa64' );
        delete( 'bspline_eval_lee_mex.mexa64' );
        addpath( path_mex );
    catch
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
    end
end

if( GenerateAll || GenerateGCodeInterpreter )
    name = "Mexing gcode interpreter : ";
    disp(name + "start" );
    try
        ReadGCodeRep = 'gen_mex/readgcode';
        path_mex = genpath( ReadGCodeRep );
        rmpath( path_mex );
        curve = coder.OutputType( 'constrCurvStructType' );
        codegen('-config', cfg,'-d', ReadGCodeRep, ...
            'constrGcodeInfoStructType',...
            'constrGcodeInfoStruct', '-args', paramsDefaultGCodeInfo( StructTypeName.MEX ),...
            'constrCurvStructType',...
            'constrCurvStruct', '-args', paramsDefaultCurv( StructTypeName.MEX ),...
            'constrHelixStruct', '-args', paramsDefaultHelix( StructTypeName.MEX ),...
            'constrHelixStructFromArcFeed', '-args', paramsDefaultHelixFromArcFeed( StructTypeName.MEX ), ...
            'constrLineStruct', '-args', paramsDefaultLine( StructTypeName.MEX ), ...
            'angles2deg', '-args', coder.typeof( zeros( 3, 1 ) ),...
            'angles2rad', '-args', coder.typeof( zeros( 3, 1 ) ),...
            'anglesNormDin', '-args', paramsDefaultAnglesNormDim( StructTypeName.MEX ),...
            'CopyCurvStruct','-args', curve,...
            'ReadGCode', '-args', { ReadGCodeCmd.Load, coder.typeof(' ', [1,1024], [0, 1]) },...
            '-o', 'ReadGCode_mex');
        disp(name + "success" );
        delete( 'ReadGCode_mex.mexa64' );
        addpath( path_mex );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
    end
end

if( GenerateAll || GenerateResampling )
    name = "Mexing resampling : ";
    disp(name + "start" );

    try
        ResamplingRep = 'gen_mex/resampling';
        path_mex = genpath( ResamplingRep );
        rmpath( path_mex );
        my_cfg  = FeedoptDefaultConfig;
%         ctx     = initFeedoptPlan( my_cfg );
        Bl      = coder.OutputType("constrBaseSplineType");
        dt      = 0.0;
        state   = ResampleState( dt );
        Curv    = constrCurvStructType;        
        codegen('-config', cfg,'-d', ResamplingRep,...
            'constrBaseSplineType',...
            'resampleCurv', '-args', {state, Bl, Curv.Info.zspdmode, ...
             coder.typeof(0.0, [Inf, 1], [1,0]), ...
             Curv.ConstJerk, dt,  Curv.a_param, Curv.b_param, ...
             my_cfg.GaussLegendreX, my_cfg.GaussLegendreW }, ...
            '-o', 'resampling_mex');
        disp(name + "success" );
        delete( 'resampling_mex.mexa64' );
        addpath( path_mex );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
    end
end

if( GenerateAll || GenerateSimplex )
    name = "Mexing simplex solver : ";
    disp(name + "start" );

    try
        CSimplexRep = 'gen_mex/c_simplex';
        path_mex = genpath( CSimplexRep );
        rmpath( path_mex );
        codegen('-config', cfg,'-d', CSimplexRep,...
            'c_simplex.m', '-args', {...
            coder.typeof(0.0,         [Inf, Inf],   [1,1]), ...
            coder.typeof(sparse(0.0), [Inf, Inf],   [1,1]), ...    % A
            coder.typeof(0.0,         [Inf, 1],     [1,0]), ...    % b
            coder.typeof( 0.0,        [Inf, Inf],   [1,1]), ...    % Aeq
            coder.typeof(0.0,         [Inf, 1],     [1,0])},...    % beq
            '-o', 'c_simplex_mex');
        disp(name + "success" );
        delete( 'c_simplex_mex.mexa64' );
        addpath( path_mex );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
    end
end

if( GenerateAll || GenerateKinematic )
    [R, P] = varTypeKinematic;
    name = "Mexing kinematics functions : ";
    disp(name + "start" );

    try
        KinematicRep = "gen_mex/kinematic/";
        path_mex = genpath( KinematicRep );
        rmpath( path_mex );

        fprintf('Mexing MGD\n')
        codegen('-config', cfg, '-d', KinematicRep,...
            KinematicsTypeName.get_fun_name( KinFunctionName.MGD ), ...
            '-args', {R, P},...
            '-o', KinematicsTypeName.get_fun_name( KinFunctionName.MGD ) ...
            + "_mex");
        
        fprintf('Mexing MGI\n')
        codegen('-config', cfg, '-d', KinematicRep,...
            KinematicsTypeName.get_fun_name( KinFunctionName.MGI ), ...
            '-args', {R, P},...
            '-o', KinematicsTypeName.get_fun_name( KinFunctionName.MGI ) ...
            + "_mex");

        fprintf('Mexing J_ar\n')
        codegen('-config', cfg, '-d', KinematicRep,...
            KinematicsTypeName.get_fun_name( KinFunctionName.J_ar ), ...
            '-args', {R, P},...
            '-o', KinematicsTypeName.get_fun_name( KinFunctionName.J_ar ) ...
            + "_mex");

        fprintf('Mexing J_ra\n')
        codegen('-config', cfg, '-d', KinematicRep,...
            KinematicsTypeName.get_fun_name( KinFunctionName.J_ra ), ...
            '-args', {R, P},...
            '-o', KinematicsTypeName.get_fun_name( KinFunctionName.J_ra ) ...
            + "_mex");

        fprintf('Mexing JP_ar\n')
        codegen('-config', cfg, '-d', KinematicRep,...
            KinematicsTypeName.get_fun_name( KinFunctionName.JP_ar ), ...
            '-args', {R, R, P},...
            '-o', KinematicsTypeName.get_fun_name( KinFunctionName.JP_ar ) ...
            + "_mex");

        fprintf('Mexing JP_ra\n')
        codegen('-config', cfg, '-d', KinematicRep,...
            KinematicsTypeName.get_fun_name( KinFunctionName.JP_ra ), ...
            '-args', {R, R, P},...
            '-o', KinematicsTypeName.get_fun_name( KinFunctionName.JP_ra ) ...
            + "_mex");

        fprintf('Mexing J2P_ar\n')
        codegen('-config', cfg, '-d', KinematicRep,...
            KinematicsTypeName.get_fun_name( KinFunctionName.J2P_ar), ...
            '-args', {R, R, R, P},...
            '-o', KinematicsTypeName.get_fun_name( KinFunctionName.J2P_ar ) ...
            + "_mex");

        fprintf('Mexing J2P_ra\n')
        codegen('-config', cfg, '-d', KinematicRep,...
            KinematicsTypeName.get_fun_name( KinFunctionName.J2P_ra), ...
            '-args', {R, R, R, P},...
            '-o', KinematicsTypeName.get_fun_name( KinFunctionName.J2P_ra ) ...
            + "_mex");

        disp(name + "success" );
        addpath( path_mex );

        delete(KinematicsTypeName.get_fun_name( KinFunctionName.MGD ) ...
            + "_mex.mexa64");
        delete(KinematicsTypeName.get_fun_name( KinFunctionName.MGI ) ...
            + "_mex.mexa64");
        delete(KinematicsTypeName.get_fun_name( KinFunctionName.J_ar ) ...
            + "_mex.mexa64");
        delete(KinematicsTypeName.get_fun_name( KinFunctionName.J_ra ) ...
            + "_mex.mexa64");
        delete(KinematicsTypeName.get_fun_name( KinFunctionName.JP_ar ) ...
            + "_mex.mexa64");
        delete(KinematicsTypeName.get_fun_name( KinFunctionName.JP_ra ) ...
            + "_mex.mexa64");
        delete(KinematicsTypeName.get_fun_name( KinFunctionName.J2P_ar ) ...
            + "_mex.mexa64");
        delete(KinematicsTypeName.get_fun_name( KinFunctionName.J2P_ra ) ...
            + "_mex.mexa64");
    catch
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
    end
end

if( GenerateAll || GenerateTridiagonalSolver )
    name = "Mexing tridiagonal solver : ";
    disp(name + "start" );

    try
        TridiagRep = 'gen_mex/tridiag';
        path_mex = genpath( TridiagRep );
        rmpath( path_mex );
        codegen('-config', cfg,'-d', TridiagRep,...
            'tridiag', '-args', {coder.typeof(0.0, [Inf, 1],   [1, 0]), ...
                             coder.typeof(0.0, [Inf, 1],   [1, 0]), ...
                             coder.typeof(0.0, [Inf, 1],   [1, 0]), ...
                             coder.typeof(0.0, [Inf, Inf], [1, 1])},...    
            '-o', 'tridiag_mex');
        disp(name + "success" );
        delete( 'tridiag_mex.mexa64' );
        addpath( path_mex );
    catch ME
        fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
    end
end

% Does not work for now
% if( GenerateFeedoptPlanRun )
%     name = "Mexing FeedoptPlanRun : ";
%     disp(name + "start" );
%     try
%         global sqrt_calls sin_calls cos_calls cot_calls DebugConfig
%         sqrt_calls = 0;
%         sin_calls = 0;
%         cos_calls = 0;
%         cot_calls = 0;
%         DebugConfig = 0;
%         FeedoptPlanRep = 'gen_mex/feedoptplanrun';
%         path_mex = genpath( FeedoptPlanRep );
%         rmpath( path_mex );
%         codegen('-config', cfg, '-d', FeedoptPlanRep,...
%             'constrCurvStructType',...
%             'ReadGCode', '-args', {ReadGCodeCmd.Load, coder.typeof(' ', [1,1024], [0, 1])},...
%             'ConstrLineStruct', '-args', {trafo, HSC, P0, P0 P0, Doff, P0, P0, P0, P0, P0, P0, 1.0, ZSpdMode.NN},...
%             'ConstrHelixStruct', '-args', {trafo, HSC, P0, P0 P0, Doff, P0, P0, P0, P0, P0, P0, P0, 1.0, P0, 1.0, 1.0, 1.0, ZSpdMode.NN},...
%             'ConstrHelixStructFromArcFeed', '-args', {trafo,  HSC, P0, P0 P0, Doff, 0,0,0,  0,0,0,  0,0,0,  P0, P0, P0, P0, 0,[0,0,0]'},...
%             'CopyCurvStruct','-args', C,...
%             'FeedoptPlanRun', '-args', fctx, ...
%             'FeedoptDefaultConfig', ...
%             'InitFeedoptPlan', '-args', fcfg,...
%             '-o', 'FeedoptPlanRun_mex');
%         disp(name + "success" );
%         delete( 'FeedoptPlanRun_mex.mexa64' );
%     catch ME
%         fprintf( ERROR_COLOR, name + "failed : " + ME.message + "\n");
%     end
% end

% Add path to current working directory
genPath = genpath( 'gen_mex' );
addpath( genPath );
