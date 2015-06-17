function nextPos = floorCompensate(legNextPos, IMU, mode)
%This functions utilize the IMU data to compensate for an angle on the
%standing surface. Mode 6 is a P regulator that compensates the height of
%the legs. Mode 5 is a non working P regulator that compensates by rotating
%legs around x and y axis.

%buffer
nextPos = legNextPos;

%P regulator that uses trigonometry to alter height.
if mode == 6

    for i = 1:6

        nextPos(i,3) = nextPos(i,3) + legNextPos(i,1)*tand(IMU(1)) - legNextPos(i,2)*tand(IMU(2));

    end
end

%P regulator that uses rotation matrices for leg compensation. non working.
if mode == 5
    xRotation = [1 0 0; 0 cosd(-IMU(1)) -sind(-IMU(1)); 0 sind(-IMU(1)) cosd(-IMU(1))];
    yRotation = [cosd(-IMU(2)) 0 -sind(-IMU(2)); 0 1 0; sind(-IMU(2)) 0 cosd(-IMU(2))];
    
    for i = 1:6
        
        nextPos = legNextPos*xRotation*yRotation;
        
    end
end

end
