function TestDynamicInterop()
    q = Queue(Queue.GCode);
    Value = struct('a', 42, 'b', 69);
    q.push(Value);
    q.push(Value);
    q.Get(2);
    q.Set(1, Value);
    DoStuffWithArray(q);
end

function DoStuffWithArray(q)
    for k = 1:q.Size
         disp(q.Get(k));
    end
end
