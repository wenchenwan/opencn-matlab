function [ cfg ] = ConfigSetSource( cfg, filename )
%#codegen
% ConfigSetSource : Set the path to the G code file.
%
% Inputs :
%   cfg         : The structure of configuration of the compuational chain
%   filename    : The path to the G code to use
%
% Outputs : 
%   cfg         : The structure of configuration of the compuational chain
%
    N = size(filename, 2);
    cfg.source(1:N) = filename;
    cfg.source(N+1:end) = 0;
end
