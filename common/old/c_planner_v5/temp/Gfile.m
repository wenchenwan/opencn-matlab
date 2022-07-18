function status = Gfile(z_inf, z_sup, precision, F)

status = 0; % success default

min_written = false;

first_x = true;
first_y = true;

dx = 0;
dy = 0;

format = strcat('%.', num2str(precision, '%.0d'), 'f');

fileID = fopen('ngc_test/spline_osc.ngc','r');
fileID2 = fopen('ngc_test/spline_osc_2.ngc','w');

while ~feof(fileID)
    
    tline = fgetl(fileID);
    
    indexX = find(tline=='X', 1);
    if (~isempty(indexX))
        
        first = indexX + 1;
        k = first;
        while ~( strcmp(tline(k), ' ') || strcmp(tline(k), '\t') || k == length(tline) )
            k = k + 1;
        end
        
        if k==length(tline)
            last = k;
        else
            last = k - 1;
        end
        
        old = tline(first:last);
        
        if first_x
            dx = str2double(old);
            new = num2str(0, format);
            first_x = false;
        else
            new = num2str(str2double(old)-dx, format);
        end
        
        newLine = replace(tline, old, new);
        tline = newLine;
         
    end
    
    
    indexY = find(tline=='Y', 1);
    if (~isempty(indexY))
        
        first = indexY + 1;
        k = first;
        while ~( strcmp(tline(k), ' ') || strcmp(tline(k), '\t') || k == length(tline) )
            k = k + 1;
        end
        
        if k==length(tline)
            last = k;
        else
            last = k - 1;
        end
        
        old = tline(first:last);

        
        if first_y
            dy = str2double(old);
            new = num2str(0, format);
            first_y = false;
        else
            new = num2str(str2double(old)-dy, format);
        end
        
        newLine = replace(tline, old, new);
        tline = newLine;
         
    end
    
    
    indexZ = find(tline=='Z', 1);
    if (~isempty(indexZ))
        
        first = indexZ + 1;
        k = first;
        while ~( strcmp(tline(k), ' ') || strcmp(tline(k), '\t') || k == length(tline) )
            k = k + 1;
        end
        
        if k==length(tline)
            last = k;
        else
            last = k - 1;
        end
        
        old = tline(first:last);
        
        if min_written
            new = num2str(z_sup, format);
            min_written = false;
        else
            new = num2str(z_inf, format);
            min_written = true;
        end
        
        newLine = replace(tline, old, new);
        tline = newLine;
         
    end
    
    indexF = find(tline=='F', 1);
    if (~isempty(indexF))
        
        first = indexF + 1;
        k = first;
        while ~( strcmp(tline(k), ' ') || strcmp(tline(k), '\t') || k == length(tline) )
            k = k + 1;
        end
        
        if k==length(tline)
            last = k;
        else
            last = k - 1;
        end

        old = tline(first:last);
        new = num2str(F);

        newLine = replace(tline, old, new);
        tline = newLine;
        
    end
    
    fprintf(fileID2, '%s\n', tline);
    
end

fclose(fileID);
fclose(fileID2);

end