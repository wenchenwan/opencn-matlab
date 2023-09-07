classdef ( Sealed ) DebugCompressing < handle
    properties
        NotCollinear;
        TooLarge;
        NotALine;
        IsAZeroStart;
        NotSameMachineParams;
        IsReallySmall;
        batchLength;
        batchZspdmode;
    end

    methods (Access = private)
        function [ obj ] = DebugCompressing
        end
    end

    methods
        function [ obj ] = reset( obj )
            obj.NotCollinear            = 0;
            obj.TooLarge                = 0;
            obj.NotALine                = 0;
            obj.IsAZeroStart            = 0;
            obj.NotSameMachineParams    = 0;
            obj.IsReallySmall           = 0;
            obj.batchLength             = [];
            obj.batchZspdmode           = [];
        end
        
        function [ obj ] = print( obj )
            disp( "Compressing Resulting tests : " );
            disp( "Not collinear : "    + obj.NotCollinear );
            disp( "Too large : "        + obj.TooLarge );
            disp( "Not alined : "       + obj.NotALine );
            disp( "Is a zero start : "  + obj.IsAZeroStart );
            disp( "Not Same Machine Parameters : "  ...
                                + obj.NotSameMachineParams );
            disp( "Is a Really Small Line : "  + obj.IsReallySmall );

            figure('Name','Distrubution of the number of curves');
            histogram(gca, obj.batchLength);
            figure('Name','Distrubution of the different zero speeds');
            c = categorical(obj.batchZspdmode, [ZSpdMode.NN, ZSpdMode.ZN, ...
                ZSpdMode.NZ, ZSpdMode.ZZ ] , {'NN', 'ZN', 'NZ', 'ZZ'});
            histogram(gca, c);
        end

        function [  ] = NotCollinearInc( obj )
            obj.NotCollinear = obj.NotCollinear + 1;
        end

        function [  ] = TooLargeInc( obj )
            obj.TooLarge = obj.TooLarge + 1;
        end

        function [  ] = NotALineInc( obj )
            obj.NotALine = obj.NotALine + 1;
        end

        function [ ] = IsAZeroStartInc( obj )
            obj.IsAZeroStart = obj.IsAZeroStart + 1;
        end

        function [ ] = NotSameMachineParamsInc( obj )
            obj.NotSameMachineParams = obj.NotSameMachineParams + 1;
        end
        
        function [] = IsReallySmallInc( obj )
            obj.IsReallySmall = obj.IsReallySmall + 1;
        end

        function [] = addBatch( obj, length, zspdmode )
            obj.batchLength( end +1 )   = length;
            obj.batchZspdmode( end + 1 )= zspdmode;
        end 

    end
    
    methods (Static)
        function [ singleObj ] = getInstance
            persistent localObj
            if ( isempty( localObj ) || ~isvalid( localObj ) )
                localObj = DebugCompressing;
                localObj.reset();
            end
            singleObj = localObj;
        end
    end
end