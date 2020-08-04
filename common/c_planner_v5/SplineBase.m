classdef SplineBase
   properties(SetAccess=private)
       ptr uint64
   end
   
   properties(SetAccess=immutable)
       degree uint32
       breaks
       ncoeff uint32
   end
   
   methods
       function this = SplineBase(degree, breaks)
           this.degree = degree;
           coder.varsize('breaks', [1, Inf], [0, 1]);
           this.breaks = breaks;
           
           this.ncoeff = size(breaks, 2) + degree - 2;
           this.ptr = bspline_create_with_breakpoints(degree, breaks);
       end
       
       function [Base0D, Base1D, Base2D, Base3D, Base1I] = base_eval(this, xvec)
           [Base0D, Base1D, Base2D, Base3D, Base1I] = bspline_base_eval(this.ptr, this.ncoeff, xvec);
       end
       
       function delete(this)
           bspline_destroy(this.ptr);
           this.ptr = 0;
       end
   end
    
end