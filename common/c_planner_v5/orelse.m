function v = orelse(value, elsevalue)
if isempty(value)
   v = elsevalue;
else
    v = value;
end
end