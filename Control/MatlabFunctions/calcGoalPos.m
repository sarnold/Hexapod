function goalPos = calcGoalPos(legCenterPos, legID, velocity, rotation, servoPos, movableLegs)
%This function draws a path inside the boundary of a given leg. The path is
%drawn in such a way that it goes through the default position and it
%utilize the current velocity and rotation. When the path is drawn a
%position on it can be chosen as goal for a lift trajectroy.

%resolution is 0.1s for the discretized path.
velocity = velocity'/10;
rotationAngle = rotation/40;

%rotation matrices
rotationMatrix = [cosd(rotationAngle) -sind(rotationAngle) 0; sind(rotationAngle) cosd(rotationAngle) 0; 0 0 1];
antiRotationMatrix = [cosd(-rotationAngle) -sind(-rotationAngle) 0; sind(-rotationAngle) cosd(-rotationAngle) 0; 0 0 1];

%get default position of this leg.
center = legCenterPos(legID,:);

%buffer up path data.
trajectoryA = zeros(301,3);
trajectoryB = zeros(301,3);
trajectoryA(1,:) = [center(1) center(2) servoPos(legID,3)];
trajectoryB(301,:) = [center(1) center(2) servoPos(legID,3)];

counter = 1;

%create path data in positive direction from default position for the leg
%until the path crosses the boundary.
while ~outsideBoundary(trajectoryA(counter,:), legID, servoPos)
    trajectoryA(1 + counter,:) = (trajectoryA(0+counter,:) + velocity)*rotationMatrix;
    counter = counter + 1;
end
countA = counter;
counter = 1;

%create path data in negative direction from default position for the leg
%until the path crosses the boundary.
while ~outsideBoundary(trajectoryB(302 - counter,:), legID, servoPos)
    trajectoryB(301 - counter,:) = (trajectoryB(302 - counter,:) - velocity)*antiRotationMatrix;
    counter = counter + 1;
end
countB = 302 - counter;


%choose amount of time needed on the path for a leg. depends on allowed
%legs in air.
if movableLegs < 2
    neededTime = 25;
elseif movableLegs < 3
    neededTime = 10;
else
    neededTime = 5;
end

%assemble the 2 paths and cut off extra buffer space.
trajectory = [trajectoryB(countB:300,:); trajectoryA(1:countA,:)];

%find that goal position
if neededTime*2 < length(trajectory)
    goalPos = trajectory(floor(length(trajectory)/2) + neededTime,:);
else
    goalPos = trajectory(end,:);
end

end