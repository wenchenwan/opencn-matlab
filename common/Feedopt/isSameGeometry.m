function [isSame] = isSameGeometry( curv1, curv2 ) %#codegen
% Check if the machine parameters are equals
isSame = false;
if( curv1.Info.Type ~= curv2.Info.Type ),                       return; end
if( curv1.Info.TRAFO ~= curv2.Info.TRAFO ),                     return; end
if( any(curv1.R0 ~= curv2.R0) ),                                return; end
if( any(curv1.R1 ~= curv2.R1) ),                                return; end
if( curv1.a_param ~= curv2.a_param ),                           return; end
if( curv1.b_param ~= curv2.b_param ),                           return; end
if( any(curv1.CorrectedHelixCenter ~= curv2.CorrectedHelixCenter) ), ...
        return; end
if( curv1.delta ~= curv2.delta ),                               return; end
if( any(curv1.CoeffP5 ~= curv2.CoeffP5) ),                      return; end
if( any(curv1.evec ~= curv2.evec) ),                            return; end
if( ~toolIsEqual(curv1.tool, curv2.tool ) ),                    return; end
if( curv1.sp_index ~= curv2.sp_index ),                         return; end
if( curv1.Info.gcode_source_line ~= curv2.Info.gcode_source_line ), return; end
isSame = true;
end