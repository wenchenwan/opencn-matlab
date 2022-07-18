function SendOptStruct(Value)
global g_QueueFinished

if coder.target('rtw')
    coder.ceval('send_opt_struct', Value);
else
    g_QueueFinished = PushStruct(g_QueueFinished, Value); 
end