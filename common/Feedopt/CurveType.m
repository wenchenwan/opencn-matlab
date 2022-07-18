classdef CurveType < int32
        enumeration 
            None(0),
            Line(1), 
            Helix(2), 
            Spline(3),
            TransP5(4)
        end
        
        methods(Static)
            function value = addClassNameToEnumNames()
                value = true;
            end
        end
end
