function [bool] = groundTouch(pos, legCenterPos)
%A function to use that determines if a leg is on ground or not.

%checks if leg is on same height as current default position. if so it's on
%ground.
if pos(3) > legCenterPos(3)-1
    bool = 1;
else
    bool = 0;
end
end