
CutOff = 0.15;

compressing=false;
cum_length=0;
nbr_segm=0;
curr_compr_sit = 1;

for i=1:ctx.q_gcode.size()
    
    l = LengthCurv(ctx, CurvStructs(i), 0, 1);
    
    if l<3*CutOff && compressing==false
        compressing = true;
        C(curr_compr_sit).start_index = i;
    end
    
    if compressing==true
        if l<3*CutOff
            cum_length = cum_length + l;
            nbr_segm = nbr_segm + 1;
        else
            C(curr_compr_sit).end_index = i-1;
            C(curr_compr_sit).cum_length = cum_length;
            C(curr_compr_sit).nbr_segm = nbr_segm;
            compressing = false;
            cum_length = 0;
            nbr_segm = 0;
            curr_compr_sit = curr_compr_sit + 1;
        end
    end
    
end