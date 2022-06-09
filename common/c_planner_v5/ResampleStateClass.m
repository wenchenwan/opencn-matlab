classdef ResampleStateClass
    properties
        u double
        ud double
        go_next logical
        dt double
        isOutsideRange logical
    end
    
    methods
        function this = ResampleStateClass(dt)
            this.u              = 0;
            this.ud             = 0;
            this.go_next        = false;
            this.isOutsideRange = false;
            this.dt             = dt;
        end
    end
end