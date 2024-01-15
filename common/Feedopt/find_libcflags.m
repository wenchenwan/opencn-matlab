function [ cflags ] = find_libcflags( name )
% find_libcflags : Find the requiered c flags for the compilation
%
% Inputs :
%   name        : Name of the required c flags
%
% Outputs :
%   cflags      : C compilation flags
%

[status, cflags] = system(sprintf("pkg-config --cflags %s", name));
ocn_assert( status == 0, "Fails to find the libraries", mfilename);

cflags = strip(cflags);

end
