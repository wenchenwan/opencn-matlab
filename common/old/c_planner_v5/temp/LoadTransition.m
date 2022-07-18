function data = LoadTransition(filename)

data = load(filename);

data.ctx = InitFeedoptPlan(data.cfg);

if data.CurvStruct1.sp_index ~= 1
    data.ctx.q_spline.push(data.Spline1);
    data.CurvStruct1.sp_index = data.ctx.q_spline.size();
end

if data.CurvStruct2.sp_index ~= 1
    data.ctx.q_spline.push(data.Spline2);
    data.CurvStruct2.sp_index = data.ctx.q_spline.size();
end


end