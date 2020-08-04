function value = c_assert(condition, message)
if coder.target('rtw')
    if ~condition
        coder.ceval('c_assert_', message);
    end    
    value = condition;
else
    assert(condition, message);
    value = condition;
end
end