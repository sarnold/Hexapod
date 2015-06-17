function [mode] = changeMode(mode, buttons)
%function allows for changing of operational mode by pressing a button on
%the hexapod. if 2 buttons are pressed simultaneous mode does not change.

if buttons == 1
    mode = 6;
elseif buttons == 2
    mode = 5;
elseif buttons == 4
    mode = 4;
elseif buttons == 8
    mode = 3;
elseif buttons == 16
    mode = 2;
elseif buttons == 32
    mode = 1;
end
end