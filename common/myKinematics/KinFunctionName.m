classdef KinFunctionName < int32
    enumeration
        Forward( 0 ), 
        Inverse( 1 ), 
        J_jt( 2 ), 
        JP_jt( 3 ), 
        J2P_jt( 4 ), 
        J_tj( 5 ), 
        JP_tj( 6 ), 
        J2P_tj( 7 ),
        Forward_complete( 8 ),
        Inverse_complete( 9 ),
        Inverse_angle( 10 )
    end
end