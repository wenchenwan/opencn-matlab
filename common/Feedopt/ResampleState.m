function [ state ] = ResampleState( dt, zeroStopTime )
    %#codegen
    % ResampleState : Interface for the ResampleStateClass in a call of 
    % the real target (see ResampleStateClass).
    %
    % Inputs :
    %   dt              : Time step
    %   zeroStopTime    : Duration of a zero stop
    %
    % Outputs :
    %   state           : State class with resampling results
    %
    coder.inline("never");
    state = ResampleStateClass( dt, zeroStopTime );
end

    
