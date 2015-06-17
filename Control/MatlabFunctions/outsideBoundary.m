function boolean = outsideBoundary(legPos, legNbr, legCurrentPos)
%Determine if a given leg position is outside a given legs boundary.

%buffer as false.
boolean = 0;

%get radius values
boundary = getBoundary();

%get anglualr width of boundary.
thetaMax = getThetaMax;

%interpolate the radius to fit the current height.
rmin = interpolateR(boundary(1,:), legPos(3));
rmax = interpolateR(boundary(2,:), legPos(3));

%Get position data for servos.
servoPos = getServoPos();
servoAngles = getServoAngle();

%Determine the current distance to the inner servo.
legPosTemp = [legPos(1:2) - servoPos(legNbr,:) legPos(3)];

%calculate the radius.
r = sqrt((legPosTemp(1))^2 + (legPosTemp(2))^2);

%if outside boundary return true.
if r > rmax || r < rmin
    boolean = 1;
end

%Rest code tests if leg is to close to adjacent legs.


legPosTemp = legPosTemp * [cosd(servoAngles(legNbr) - 90) -sind(servoAngles(legNbr) - 90) 0; sind(servoAngles(legNbr) - 90) cosd(servoAngles(legNbr) - 90) 0; 0 0 1];

theta = acosd(legPosTemp(1)/r);

if abs(theta - 90) > thetaMax
    boolean = 1;
end

switch legNbr
    case 1
        if legPos(2) < legCurrentPos(legNbr+1, 2)+30
            boolean = 1;
        end
    case 2
        if legPos(2) > legCurrentPos(legNbr-1, 2)-30
            boolean = 1;
        end
        if legPos(2) < legCurrentPos(legNbr+1, 2)+30
            boolean = 1;
        end
    case 3
        if legPos(2) > legCurrentPos(legNbr-1, 2)-30
            boolean = 1;
        end
    case 4
        if legPos(2) < legCurrentPos(legNbr+1, 2)+30
            boolean = 1;
        end
    case 5
        if legPos(2) > legCurrentPos(legNbr-1, 2)-30
            boolean = 1;
        end
        if legPos(2) < legCurrentPos(legNbr+1, 2)+30
            boolean = 1;
        end
    case 6
        if legPos(2) > legCurrentPos(legNbr-1, 2)-30
            boolean = 1;
        end
end

end