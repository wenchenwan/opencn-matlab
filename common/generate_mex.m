clear; clc;

% We need first to choose what we whant to MEX.
% Several options are possible.
GenerateAll = true;

if( ~GenerateAll )
    GenerateConstrFunctions     = false;
    GenerateResampling          = false;
    GenerateGCodeInterpreter    = false;
    GenerateQueues              = false;
    GenerateSimplex             = false;
    GenerateSpline              = false;
%     GenerateFeedoptPlanRun      = false; % Does not work now
    GenerateKinematic           = false;
end

cfg = generate_mex_config();

% Some entry-point functions (memebers of codegen functions list)
% take output of the functions hereafter, as arguments.
% 'FeedoptDefaultConfig' and 'InitFeedoptPlan' must be entry-points functions, as well.
fcfg = coder.OutputType('FeedoptDefaultConfig');
fctx = coder.OutputType('InitFeedoptPlan');
C = coder.OutputType('ConstrCurvStructType');

global DebugActive sqrt_calls
DebugActive = false;
sqrt_calls = 0;

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

if( GenerateAll || GenerateConstrFunctions )
    name = "Debug Constr functions : ";
    disp(name + "start" );
    try
        DebugRep = 'gen_mex/debug';
        path_mex = genpath( DebugRep );

%         codegen('-config', cfg,'-d', DebugRep , ...
%             'constrLineStruct', '-args', paramsDefaultLine( StructTypeName.MEX ),...
%             '-o', 'debug_mex' ); 
%         codegen('-config', cfg,'-d', DebugRep , ...
%             'constrGcodeInfoStructType',...
%             'constrGcodeInfoStruct', '-args', paramsDefaultGCodeInfo( StructTypeName.MEX ),...
%             'constrBaseSplineType',...
%             'constrBaseSpline', '-args', paramsDefaultBaseSpline( StructTypeName.MEX ),...
%             'constrSplineType',...
%             'constrSpline', '-args', paramsDefaultSpline( StructTypeName.MEX ),...
%             'constrCurvStructType',...
%             'constrCurvStruct', '-args', paramsDefaultCurv( StructTypeName.MEX ),...
%             '-o', 'debug_mex' );
        disp(name + "success" );
        delete( 'debug_mex.mexa64' );
        addpath( path_mex );
    catch ME
        disp(name + "failed : " + ME.message );
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
        disp(name + "failed : " + ME.message );
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
        disp(name + "success" );
        delete( 'bspline_create_mex.mexa64' );
        delete( 'bspline_destroy_mex.mexa64' );
        delete( 'bspline_base_eval_mex.mexa64' );
        delete( 'bspline_eval_mex.mexa64' );
        addpath( path_mex );
    catch
        disp(name + "failed" );
    end
end

if( GenerateAll || GenerateGCodeInterpreter )
    name = "Mexing gcode interpreter : ";
    disp(name + "start" );
    try
        ReadGCodeRep = 'gen_mex/readgcode';
        path_mex = genpath( ReadGCodeRep );
        rmpath( path_mex );
        codegen('-config', cfg,'-d', ReadGCodeRep, ...
            'ConstrCurvStructType',...
            'ReadGCode', '-args', {ReadGCodeCmd.Load, coder.typeof(' ', [1,1024], [0, 1])},...
            'ConstrLineStruct', '-args', {trafo, HSC, P0, P0 P0, Doff, P0, P0, P0, P0, P0, P0, 1.0, ZSpdMode.NN},...
            'ConstrHelixStruct', '-args', {trafo, HSC, P0, P0 P0, Doff, P0, P0, P0, P0, P0, P0, P0, 1.0, P0, 1.0, 1.0, 1.0, ZSpdMode.NN},...
            'ConstrHelixStructFromArcFeed', '-args', {trafo,  HSC, P0, P0 P0, Doff, 0,0,0,  0,0,0,  0,0,0,  P0, P0, P0, P0, 0,[0,0,0]'},...
            'CopyCurvStruct','-args', C,...
            '-o', 'ReadGCode_mex');
        disp(name + "success" );
        delete( 'ReadGCode_mex.mexa64' );
        addpath( path_mex );
    catch ME
        disp(name + "failed : " + ME.message );
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
        ctx     = InitFeedoptPlan( my_cfg );
        dt      = my_cfg.dt;
        state   = ResampleState( dt );
        Curv    = ConstrCurvStructType;        
        codegen('-config', cfg,'-d', ResamplingRep,...
            'resampleCurv', '-args', {state, ctx.Bl, Curv.zspdmode, ...
             coder.typeof(0.0, [Inf, 1], [1,0]), ...
             Curv.ConstJerk, dt,  Curv.a_param, Curv.b_param }, ...
            '-o', 'resampling_mex');
        disp(name + "success" );
        delete( 'resampling_mex.mexa64' );
        addpath( path_mex );
    catch ME
        disp(name + "failed : " + ME.message );
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
        disp(name + "failed : " + ME.message );
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
%             'ConstrCurvStructType',...
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
%         disp(name + "failed : " + ME.message );
%     end
% end

if( GenerateAll || GenerateKinematic )
    name = "Mexing kinematics functions : ";
    disp(name + "start" );
    
    try
        KinematicRep = "gen_mex/kinematic";
    
        fprintf('Mexing MGD\n')
        codegen('-config', cfg, '-d', KinematicRep + "/MGD",...
                'MGD', '-args', {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},...
                '-o', 'MGD_mex');
        
        fprintf('Mexing MGI\n')
        codegen('-config', cfg, '-d', KinematicRep + "/MGI",...
                'MGI', '-args', {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},...
                '-o', 'MGI_mex');
        
        fprintf('Mexing J_ar\n')
        codegen('-config', cfg, '-d', KinematicRep + "/J_ar",...
                'J_ar', '-args', {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},...
                '-o', 'J_ar_mex');

        fprintf('Mexing J_arP\n')
        codegen('-config', cfg, '-d', KinematicRep + "/J_arP",...
                'J_arP', '-args', {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},...
                '-o', 'J_arP_mex');

        fprintf('Mexing J_arPP\n')
        codegen('-config', cfg, '-d', KinematicRep + "/J_arPP",...
                'J_arPP', '-args', {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0},...
                '-o', 'J_arPP_mex');
        
%         fprintf('Mexing BackwardJacobian\n')
%         codegen('-config', cfg, '-d', KinematicRep + "/BackwardJacobian",...
%                 'BackwardJacobian', '-args', {d51},...
%                 '-o', 'BackwardJacobian_mex');
% 
%         fprintf('Mexing Velocity\n')
%         codegen('-config', cfg, '-d', KinematicRep + "/Velocity",...
%                 'Velocity', '-args', {d51, d35},...
%                 '-o', 'Velocity_mex');

        disp(name + "success" );

        delete('MGD_mex.mexa64');
        delete('MGI_mex.mexa64');
        delete('J_ar_mex.mexa64');
        delete('J_arP_mex.mexa64');
        delete('J_arPP_mex.mexa64');
%         delete('BackwardJacobian_mex.mexa64');
%         delete('Velocity_mex.mexa64');

    catch
        disp(name + "failed" );
    end
end

% Add path to current working directory
genPath = genpath( 'gen_mex' );
addpath( genPath );