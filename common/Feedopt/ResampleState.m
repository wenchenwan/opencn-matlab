function state = ResampleState(dt, zeroStopTime)
    coder.inline("never");
    state = ResampleStateClass(dt, zeroStopTime);
end

    