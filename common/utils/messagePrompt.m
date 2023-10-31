function [] = messagePrompt( queryMsg )
%messagePrompt
% Write a message in the prompt, the user needs to enter Y to continue.
% Inputs :
%   queryMsg : string : (optional) Msg to display in the prompt
%
if( coder.target("MATLAB") )
    if( nargin < 1 )
        queryMsg = "Do you want to continue ?";
    end
    pause(0.5);

    prompt = queryMsg + " Y/N [Y]: ";
    txt = input(prompt,"s");
    if isempty(txt) || txt == 'N'
        error( "Program stopped by user...");
    end
end

end