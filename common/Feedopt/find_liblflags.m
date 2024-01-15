function [ lflags ] = find_liblflags( name )
% find_libcflags : Find the requiered l flags for the compilation
%
% Inputs :
%   name        : Name of the required l flags
%
% Outputs :
%   lflags      : L compilation flags
%
[status, lflags] = system(sprintf("pkg-config --libs %s", name));
ocn_assert( status == 0, "Fails to find the libraries", mfilename);

lflags = strip(lflags);

end
