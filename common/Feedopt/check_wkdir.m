function [] = check_wkdir()
% Check if the current directory is the working directory
if( ~strcmp( flip( strtok( flip( pwd ) , '/' ) ), 'common') )
    error( 'Wrong directory, you should run the script from working driectory' ); 
end

end