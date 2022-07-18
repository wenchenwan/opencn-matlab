classdef ( Sealed ) DebugCompressing < handle
    properties
        NotCollinear;
        TooLarge;
        NotALine;
    end

    methods (Access = private)
        function [ obj ] = DebugCompressing
        end
    end

    methods
        function [ obj ] = reset( obj )
            obj.NotCollinear    = 0;
            obj.TooLarge        = 0;
            obj.NotALine        = 0;
        end
        
        function [ obj ] = print( obj )
            disp( "Not Collinear : "    + obj.NotCollinear );
            disp( "Too large : "        + obj.TooLarge );
            disp( "Not alined : "       + obj.NotALine );
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