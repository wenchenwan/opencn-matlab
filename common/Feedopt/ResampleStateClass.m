classdef ResampleStateClass
    properties
        u               double          % Time scaling parameter 
        ud              double          % First derivative of u
        udd             double          % Second derivative of u
        uddd            double          % Third derivative of u
        dt              double          % Discretization time
        go_next         logical         % Need to go the next curv structure
        isOutsideRange  logical         % The u parameter is outsite the range
        isAStop         logical         % The curvstruct is a stop (zero speed)
        stopCounter     int32           % Counter for the number of time step at stop
        zeroStopTime    int32           % Number of time step used to stay in stop
    end
    
    methods
        function [this] = ResampleStateClass(dt, zeroStopTime)
            this.dt             = dt;
            this.zeroStopTime   = zeroStopTime;
            % Reset the parameters to default values
            this.u              = 0;
            this.ud             = 0;
            this.udd            = 0;
            this.uddd           = 0;
            this.go_next        = false;
            this.isOutsideRange = false;
            this.isAStop        = false;
            this.stopCounter    = 0;
        end

        function [this] = setZeroStop(this, dt, zeroStopTime)
            this.dt             = dt;
            this.u              = 1;
            this.ud             = 0;
            this.udd            = 0;
            this.uddd           = 0;
            this.go_next        = false;
            this.isOutsideRange = false;
            this.isAStop        = true;
            this.stopCounter    = zeroStopTime;
            this.zeroStopTime   = zeroStopTime;
        end

        function [this] = setU(this, u, ud, udd, uddd )
            this.u      = u;
            this.ud     = ud;
            this.udd    = udd;
            this.uddd   = uddd;
        end

        function [u, ud, udd, uddd] = getU(this)
            u       = this.u;
            ud      = this.ud;
            udd     = this.udd;
            uddd    = this.uddd;
        end

        function [this] = decreaseStopCounter(this)
            this.stopCounter    = this.stopCounter -1;
            if( this.stopCounter <= 0 )
                this.isAStop        = false;
                this.go_next        = true;
                this.isOutsideRange = true;
            end
        end

        function [this] = startZeroStopTime( this )
            this = this.setZeroStop( this.dt, this.zeroStopTime );
        end
    end
end