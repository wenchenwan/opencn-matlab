classdef ( Sealed ) DebugResampling < handle
    % DebugResampling : Singleton class type used to debug the resampling.
    %
    % Functionalities : 
    %   + Keep track of the following : 
    %         - counter on u negative value
    %         - counter on u not increasing value
    %         - counter on t negative value
    %         - counter on t larger then provided bounds
    %         - counter on the number of u values
    %         - counter on the number of curves used in the resampling
    %         - counter on q(u) negative
    %         - counter on u not real
    %         - counter on u NaN
    %         - counter on t not real
    %         - counter on t is NaN
    %
    properties
        flagDoPlot;
        countUNegative;
        countUNotIncreasing;
        countTNegative;
        countTTooLarge;
        countUTot;
        countNbCurv;
        countQNegative;
        countUNotReal;
        countUNan;
        countTNotReal;
        countTNan;
        dtVec;
    end

    methods (Access = private)
        function [ obj ] = DebugResampling
            obj.reset();
        end
    end

    methods
        function [ obj ] = reset( obj )
            obj.flagDoPlot              = false;
            obj.countUNegative          = 0;
            obj.countUNotIncreasing     = 0;
            obj.countUNotReal           = 0;
            obj.countUNan               = 0;
            obj.countTNotReal           = 0;
            obj.countTNan               = 0;
            obj.countTNegative          = 0;
            obj.countTTooLarge          = 0;
            obj.countUTot               = 0;
            obj.countQNegative          = 0;
            obj.countNbCurv             = 0;
            obj.dtVec                   = [];
        end

        function [ obj ] = print( obj )
            disp( "****************************************************" );
            disp( "Resampling results : " );
            disp( "U negative : "       + obj.countUNegative );
            disp( "U not increasing : " + obj.countUNotIncreasing );
            disp( "U not real : "       + obj.countUNotReal );
            disp( "U nan : "            + obj.countUNan );
            disp( "T not reak : "       + obj.countTNotReal );
            disp( "T nan : "            + obj.countTNan );
            disp( "T negative : "       + obj.countTNegative );
            disp( "T too large : "      + obj.countTTooLarge );
            disp( "U total : "          + obj.countUTot );
            disp( "Q Negative : "       + obj.countQNegative );
            disp( "Nb curves : "        + obj.countNbCurv );
            disp( "****************************************************" );

            if( obj.flagDoPlot )
                messagePrompt();
            end
        end
        
        function [ obj ] = addDT( obj, dt )
            obj.dtVec( end + 1 ) = dt;
        end

        function [ obj ] = increaseUNegativeCounter( obj )
            obj.countUNegative = obj.countUNegative + 1;
        end
        
        function [ obj ] = increaseUNotIncreasingCounter( obj )
            obj.countUNotIncreasing = obj.countUNotIncreasing + 1;
        end

        function [ obj ] = increaseUNotRealCounter( obj )
            obj.countUNotReal = obj.countUNotReal + 1;
        end

        function [ obj ] = increaseUNanCounter( obj )
            obj.countUNan = obj.countUNan + 1;
        end

        function [ obj ] = increaseTNanCounter( obj )
            obj.countTNan = obj.countTNan + 1;
        end

        function [ obj ] = increaseTNegativeCounter( obj )
            obj.countTNegative = obj.countTNegative + 1;
        end
        
        function [ obj ] = increaseTTooLargeCounter( obj )
            obj.countTTooLarge = obj.countTTooLarge + 1;
        end

        function [ obj ] = increaseUCounter( obj )
            obj.countUTot = obj.countUTot + 1;
        end

        function [ obj ] = increaseQNegativeCounter( obj )
            obj.countQNegative = obj.countQNegative + 1;
        end
        
        function [ obj ] = increaseNbCurvCounter( obj )
            obj.countNbCurv = obj.countNbCurv + 1;
        end

    end

    methods (Static)
        function [ singleObj ] = getInstance
            persistent localObj
            if ( isempty( localObj ) || ~isvalid( localObj ) )
                localObj = DebugResampling;
            end
            singleObj = localObj;
        end
    end
end