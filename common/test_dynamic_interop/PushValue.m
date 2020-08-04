function PushValue(Value)
persistent TheArray
if coder.target('rtw')
    coder.ceval('push_value', Value);
else
    if isempty(TheArray)
        TheArray = [];
    end
    
    TheArray = [TheArray Value];
end
end