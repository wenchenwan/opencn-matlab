%% Select a directory containing the G code files to parse.
close all; clear; clc;

DirName = uigetdir(pwd + "/", 'Select GCode folder');
listing = dir( DirName );

if( ~isempty( listing(1).name ) )
    listFiles = {listing.name};
    listFolder = {listing.folder};
else
    error( "Files not found..." );
end

%% Parse the different G codes, looking for specific pattern
%  The results are stored in a csv file

csvOutoutFileName = "Gcodes.csv";
columnNames       = [ "File_name"; "G_commandes"; "M_commandes"; "All" ];
pattern( 1 )      = "G" + ( digitsPattern(1) | digitsPattern(2) ) + (" " | ";" | "." + digitsPattern(1) | lineBoundary );
pattern( 2 )      = "M" + ( digitsPattern(1) | digitsPattern(2) ) + (" " | ";" | "." + digitsPattern(1) | lineBoundary );
listFiles = listFiles( contains( listFiles,".ngc" ) );

NumberFiles      = length( listFiles );
NumberColumns    = length( columnNames );

res = zeros( NumberFiles, NumberColumns ) + "";

disp( "Parsing started" );

patternJoinCol = ", "; patternJoinList = " ";

fid = fopen( csvOutoutFileName, "w" );
fprintf( fid, columnNames.join( patternJoinCol ) + "\n");

for ind = 1 : NumberFiles
    file_name = listFolder{ ind } + "/" + listFiles{ ind };

    res( ind, 1 ) = listFiles{ ind };
    
    disp( res( ind, 1 ) + " : started");
    
    for k = 1 : NumberColumns -2
        [ list ] = read_file( file_name, pattern(k) );
        res( ind, k + 1 ) = list.join( patternJoinList );
    end

%     fprintf( fid, res( ind, : ).join( patternJoinCol ) + "\n");

    [ list ] = read_file( file_name, pattern );
    res( ind, NumberColumns ) = list.join( patternJoinList );

    fprintf( fid, res( ind, : ).join( patternJoinCol ) + "\n");

    disp( res( ind, 1 ) + " : finished");
end

fclose( fid );

disp( "Parsing finished" );
uiimport( csvOutoutFileName );

%--------------------------------------------------------------------------
function [ lists ] = read_file( file_name, pattern )
% read_file : Read a file and look for specific pattern.
% Inputs :
%   file_name   : The file name to parsed
%   pattern     : The patern to search 
%
% Ouputs :
%   lists       : List of matching patterns
fid = fopen( file_name, "r" );

lists = [];

tline = fgetl(fid);
if length(pattern) == 1
    while ischar(tline)
        % Search for matching pattern
        str = extract( string( tline) , pattern );
        % Append pattern only if new one
        if( ~isempty( str ) ), lists = unique( [lists; str] ); end
        % Extract next line
        tline = fgetl(fid);
    end
else
    while ischar(tline)
        % Search for matching pattern
        str1 = extract( string( tline) , pattern(1) );
        str2 = extract( string( tline) , pattern(2) );
        % Both patterns in same line
        if( ~isempty( str1 ) && ~isempty( str2 ) )
            lists = unique( [lists; "1"] );
        end
        % Extract next line
        tline = fgetl(fid);
    end
end

if( isempty( lists ) ), lists = ""; end

fclose(fid);
end
% parse_GCodes.m
% Affichage de parse_GCodes.m