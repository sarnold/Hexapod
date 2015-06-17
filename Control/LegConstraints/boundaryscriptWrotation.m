boundary = getBoundary();
%This code can be used to plot a boundary for a leg. Code is very similar
%to calcGoalPos.m.

legID = 5;
servo = getServoPos();
degreeRange = 50;
servoAngle = getServoAngle();
servoPos = [-185.9805   180.2313    70.0000;
            -240.0000   0           70.0000;
            -185.9805   -180.2313   70.0000;
            185.9805    180.2313    70.0000;
            240.0000    0           70.0000;
            185.9805    -180.2313   70.0000];

rmax = interpolateR(boundary(2,:), servoPos(legID,3));
rmin = interpolateR(boundary(1,:), servoPos(legID,3));

rcenter = interpolateR(getLegCenter(), servoPos(legID,3));

l1 = linspace(-400,400,4);
legline1 = [l1; ones(1,length(l1)).*servoPos(mod(legID-2,6)+1,2) - 30]';
legline2 = [l1; ones(1,length(l1)).*servoPos(mod(legID,6)+1,2) + 30]';
    

velocity = [0 35 0]/10;

center = [servo(legID,1) + rcenter*cosd(servoAngle(legID)) servo(legID,2) + rcenter*sind(servoAngle(legID)) servoPos(legID,3)];

t1 = linspace(servoAngle(legID)-degreeRange,servoAngle(legID)+degreeRange,10);
t2 = linspace(servoAngle(legID)+degreeRange,servoAngle(legID)-degreeRange,10);

boundary = [servo(legID,1) + rmin * cosd(t1') servo(legID,2) + rmin * sind(t1')];

boundary = [boundary; (servo(legID,1) + rmax * cosd(t2')) (servo(legID,2) + rmax * sind(t2'))];

boundary = [boundary; boundary(1,:)];
trajectoryA = zeros(301,3);
trajectoryB = zeros(301,3);
trajectoryA(1,:) = [center(1) center(2) servoPos(legID,3)];
trajectoryB(301,:) = [center(1) center(2) servoPos(legID,3)];

rotationAngle = 20/40;
rotationMatrix = [cosd(-rotationAngle) -sind(-rotationAngle) 0; sind(-rotationAngle) cosd(-rotationAngle) 0; 0 0 1];
antiRotationMatrix = [cosd(rotationAngle) -sind(rotationAngle) 0; sind(rotationAngle) cosd(rotationAngle) 0; 0 0 1];

x = [0 0];
y = [0 0];
findA = 0;
findB = 0;
counter = 1;

while ~outsideBoundary(trajectoryA(counter,:), legID, servoPos)
    trajectoryA(1 + counter,:) = (trajectoryA(0+counter,:) - velocity)*antiRotationMatrix;
    counter = counter + 1;
end
countA = counter;
counter = 1;

while ~outsideBoundary(trajectoryB(302 - counter,:), legID, servoPos)
    trajectoryB(301 - counter,:) = (trajectoryB(302 - counter,:) + velocity)*rotationMatrix;
    counter = counter + 1;
end

countB = 302 - counter;

trajectory = [trajectoryB(countB:300,:); trajectoryA(1:countA,:)];

plot(boundary(:,1), boundary(:,2), '-');
hold on
plot(legline1(:,1), legline1(:,2), '-');
plot(legline2(:,1), legline2(:,2), '-');
plot(servo(legID,1), servo(legID,2), '+');
plot(trajectory(:,1), trajectory(:,2), '-');
plot(center(1), center(2), '+')
%plot(-185, -180, '*')
xlim([0 350]);
ylim([-200 200]);
hold off

xlabel('x [mm]');
ylabel('y [mm]');
print('-dpng','-r400','trajectory')