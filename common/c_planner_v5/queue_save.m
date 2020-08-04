function queue_save(ptr, filename) %#codegen
    value = queue_get(ptr, 1);
    fields = getfields(value);
    
    fid = fopen(filename, 'wb');
    
    for kfield = 1:length(fields)
        field = fields{kfield};
    end
    
    fclose(fid);
end