function saveResults( ngcFilePath )

check_wkdir();

folderName = "result";

if( ~exist( folderName , 'dir' ) ), mkdir( folderName ); end

disp("****************************************************");
disp("SAVE RESULTS :")

[ currentTimerString ] = get_folder_name();

folderName = folderName + filesep + currentTimerString;

mkdir( folderName )

disp( "Start to save results : " + folderName );

figHandles = findobj('Type', 'figure');

count = 0;
[ listFigNames ] = get_figures_name();

for f_ = figHandles'
    count = count + 1;

    filePath = folderName + filesep + listFigNames(count);
    saveas( f_, filePath )
    disp( "Save figure :" + filePath );
    if( count == 6 ) break; end
end

disp("Copy FeedrateDefault config");
copyfile("./Feedopt/FeedoptDefaultConfig.m", folderName + filesep + "FeedoptDefaultConfig.m" );

disp("Copy basicExample");
copyfile("./basic_example.m", folderName + filesep + "basic_example.m" );

disp("Copy Ngc file");
[ ngcFileName ] = extract_filename( ngcFilePath );
copyfile("." + filesep + ngcFilePath, folderName + filesep + ngcFileName );

disp("Copy run csv data");
copyfile(".tmp.csv", folderName + filesep + "data.csv");

disp("Copy log file");
[ latestLogFilePath, logFileName ] = get_last_log_file();
copyfile(latestLogFilePath, folderName + filesep + logFileName );

disp("Create git info file");
system( "./utils/write_git_info.bash " + folderName + filesep + "git_info.txt" );

end

function [ listFigNames ] = get_figures_name()

listFigNames = [ "06_normalized_jerk", "04_normalized_velocity", "03_position",
    "05_normalized_acceleration", "02_computed_feedrate", "01_overview"];

end

function [ formattedString ] = get_folder_name()

% Obtenir la date et l'heure actuelles
currentDateTime = datetime('now', 'Format', 'yyyyMMdd-HHmmss');

% Convertir en chaîne de caractères
formattedString = datestr(currentDateTime, 'yymmdd-HHMMSS');

end

function [ latestFilePath, latestFile ] = get_last_log_file()
% Spécifiez le chemin du dossier
folderPath = './logs';

% Obtenez la liste des fichiers dans le dossier
files = dir(fullfile(folderPath, 'logs_*.txt'));

% Vérifiez s'il y a des fichiers dans le dossier
if isempty(files)
    disp('Aucun fichier trouvé dans le dossier.');
    return;
end

% Triez les fichiers par date de modification (du plus récent au plus ancien)
[~, idx] = sort([files.datenum], 'descend');

% Obtenez le fichier le plus récent
latestFile = files(idx(1)).name;

% Affichez le nom du fichier le plus récent
disp(['Le fichier le plus récent est : ' latestFile]);

% Vous pouvez également obtenir le chemin complet du fichier ainsi :
latestFilePath = fullfile(folderPath, latestFile);
end

function [ fileName ] = extract_filename( filePath )
% Utilisez fileparts pour obtenir le nom du fichier avec l'extension
[~, fileNameWithExtension, ext] = fileparts(filePath);

fileName = "" + fileNameWithExtension + ext;

end