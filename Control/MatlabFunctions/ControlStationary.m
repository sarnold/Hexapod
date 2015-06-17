function [velocity, rotation] = ControlStationary(velocity, rotation)
%Just helps determine an interval where the levers on the contoller is in
%middle position. Threshhold is an absolute value of 3 at the moment.


for i = 1:2
    if abs(velocity(i)) <= 3
        velocity(i) = 0;
    end
    if abs(rotation(i)) <= 3
        rotation(i) = 0;
    end
end
end