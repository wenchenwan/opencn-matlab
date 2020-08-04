classdef ResampleStateClass
    properties
        u double
        go_next logical
        dt double
    end
    
    methods
        function this = ResampleStateClass(dt)
            this.u = 0;
            this.go_next = false;
            this.dt = dt;
        end
    end
end