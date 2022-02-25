function opt_structs = TestFeedoptPlan2()
    cfg = FeedoptDefaultConfig();
    cfg.source = 'ngc_test/test_long.ngc';
    cfg.DebugPrint = false;
    cfg.LSplit = 100;
    sws = FeedoptStaticWorkspace(cfg);
    dws = FeedoptDynamicWorkspace(cfg);
    
%     dws = FeedoptPlan2(sws, dws, cfg);
    k = 1;
    while ~dws.reached_end
        dws = FeedoptRead(sws,dws,cfg);
        if dws.gcode.Type ~= 0
            opt_structs(k) = dws.gcode;
            k = k + 1;
        end
    end
    
end

function dws = FeedoptPlan2(sws, dws, cfg)
    while ~dws.reached_end
        dws = FeedoptOptimize(sws, dws, cfg);
    end
end

function dws = FeedoptRead(sws, dws, cfg)
    if dws.file_opened
        [status, dws.gcode] = ReadGCode(ReadGCodeCmd.Read, '');
        if status == 0
            dws.reached_end = true;
        end
    else
        status = ReadGCode(ReadGCodeCmd.Load, cfg.source);
        if status
            dws.file_opened = true;
            dws.reached_end = false;
        else
            dws.file_opened = false;
            dws.reached_end = true;
        end
    end
end

function dws = FeedoptSmooth(sws, dws, cfg)
    fprintf('FeedoptSmooth\n')
    while dws.gcode1.Type == 0 && ~dws.reached_end
        dws = FeedoptRead(sws, dws, cfg);
        if dws.gcode.Type ~= 0
%             PrintCurvStruct(dws.gcode);
            dws.gcode1 = dws.gcode2;
            dws.gcode2 = dws.gcode;
        end
    end
    
    if dws.gcode1.Type ~= 0 && dws.gcode2.Type == 0
        if dws.smooth.C2.Type ~= 0
            dws.smooth1 = dws.smooth.C2;
        else
            dws.smooth1 = dws.gcode1;
        end
    elseif dws.gcode1.Type ~= 0 && dws.gcode2.Type ~= 0
        if dws.smooth.C2.Type == 0
            [dws.smooth.C1, dws.smooth.CT, dws.smooth.C2] = CalcTransition(ctx, dws.gcode1, dws.gcode2, cfg.CutOff);
        else
            [dws.smooth.C1, dws.smooth.CT, dws.smooth.C2] = CalcTransition(ctx, dws.smooth.C2, dws.gcode2, cfg.CutOff);
        end
        dws.smooth1 = dws.smooth.C1;
        dws.smooth2 = dws.smooth.CT;
    end
    
    dws.gcode1.Type = 0;
    
end


function dws = FeedoptSplit(sws, dws, cfg)
    fprintf('FeedoptSplit\n')
    while dws.smooth1.Type == 0 && ~dws.reached_end
        dws = FeedoptSmooth(dws, dws, cfg);
    end
    
    if dws.smooth1.Type ~= 0
        CurvSplit = SplitCurvStruct(dws.smooth1, cfg.LSplit);
        dws.curv_split(dws.n_split+1:dws.n_split+length(CurvSplit)) = CurvSplit;
        dws.n_split = dws.n_split + length(CurvSplit);
        dws.smooth1 = dws.smooth2;
        dws.smooth2.Type = 0;
    end
end

function dws = FeedoptOptimize(sws, dws, cfg)
    while dws.n_split < cfg.NHorz && ~dws.reached_end
        dws = FeedoptSplit(sws, dws, cfg);
    end
    
    dws.curv_split(1:dws.n_split-1) = dws.curv_split(2:dws.n_split);
    dws.n_split = dws.n_split - 1;
end


function ws = FeedoptStaticWorkspace(cfg)
    ws.Bl = bspline_create(0, 1, cfg.SplineDegree, cfg.NBreak);
    ws.u_vec = sinspace(0, 1, cfg.NDiscr);
    [BasisVal, BasisValD, BasisValDD, BasisIntegr] = bspline_base_eval(ws.Bl, ws.u_vec); 
    ws.BasisVal     = BasisVal;
    ws.BasisValD    = BasisValD;
    ws.BasisValD    = BasisValDD;
    ws.BasisIntegr  = BasisIntegr;
end

function ws = FeedoptDynamicWorkspace(cfg)
    ws.v_0 = cfg.v_0;
    ws.v_1 = cfg.v_1;
    ws.at_0 = cfg.at_0;
    ws.at_1 = cfg.at_1;
    
    trafo = false; % TRAFO flag disable 
    HSC = false;
    Poff = zeros(3, 1); Aoff = Poff; Uoff = Poff; Doff = 0.0;
    A0 = zeros(3,1); A1 = A0; U0 = A0 ; U1 = A0; 

    ws.opt_curv = ConstrLineStruct(trafo, HSC, Poff, Aoff, Uoff, ...
                               Doff, [1,2,3]', [4,5,6]', A0, A1, U0, ...
                               U1, 0.7, ZSpdMode.NN);
    ws.opt_curv.Type = 0;
    
    ws.n_split = 0;
    ws.curv_split = repmat(ws.opt_curv, [1, 1024]);
    
    ws.smooth.C1 = ws.opt_curv;
    ws.smooth.CT = ws.opt_curv;
    ws.smooth.C2 = ws.opt_curv;
    
    ws.smooth1 = ws.opt_curv;
    ws.smooth2 = ws.opt_curv;
    
    ws.gcode1 = ws.opt_curv;
    ws.gcode2 = ws.opt_curv;
    ws.gcode = ws.opt_curv;
    
    ws.reached_end = false;
    ws.file_opened = false;
end