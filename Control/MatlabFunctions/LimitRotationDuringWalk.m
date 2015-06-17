function [velocity, rotation] = LimitRotationDuringWalk(velocity, rotation)
%Both walking and rotation provides complications. Best way so far is to
%limit the rotation velocity during walk. Different limits apply to
%different walking speeds.

if sqrt(sum(velocity.^2)) > 0
    if abs(rotation(1)) > 50
        rotation(1) = 50*sign(rotation(1));
    end
end
if sqrt(sum(velocity.^2)) > 30
    if abs(rotation(1)) > 30
        rotation(1) = 30*sign(rotation(1));
    end
end
if sqrt(sum(velocity.^2)) > 60
    if abs(rotation(1)) > 15
        rotation(1) = 15*sign(rotation(1));
    end
end
end