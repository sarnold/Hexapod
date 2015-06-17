function [movableLegs, velocity, rotation, nerf, time] = legLimit(velocity, rotation, queue, legsInAir, mode)
%Amount of legs the hexapod is allowed to use determined by current speed
%and rotationvelocity and mode. mode 1 is currently the best one. mode 2 is
%insufficient. mode 3 is currently identical with mode 1.

persistent Velocity;
persistent Rotation;

movableLegs = max(sum(legsInAir),1);
nerf = 0;

if isempty(Velocity)
    Velocity = velocity;
end
if isempty(Rotation)
    Rotation = rotation;
end

legsOnGround = 6 - sum(legsInAir);
time = 1000;

if mode == 1
    
    %absolute values are required.
    rotationTemp = abs(rotation);
    speed = sqrt(sum(velocity.^2));

    %During pure rotation.
    if speed == 0
        if rotationTemp(1) < 35
            movableLegs = 1;
        elseif rotationTemp(1) >= 35 && rotationTemp(1) < 80
            movableLegs = 2;
        else
            movableLegs = 3;
        end

    %During pure walking.    
    elseif rotationTemp(1) == 0
        if speed < 20
            movableLegs = 1;
        elseif speed >= 20 && speed < 60
            movableLegs = 2;
        else
            movableLegs = 3;
        end

    %If both walking and rotating, better use all 3 legs ;)
    else
        movableLegs = 3;
    end

elseif mode == 2

    lowTime = min(queue(2,1:legsOnGround));
    highTime = max(queue(2,1:legsOnGround));
    timespan = highTime - lowTime;

    belowPointFive = 0;
    belowOne = 0;
    belowTwo = 0;
    belowThree = 0;

    for i = 1:legsOnGround
        if queue(2,i) < 0.5
            belowPointFive = belowPointFive + 1;        
        elseif queue(2,i) < 1
            belowOne = belowOne + 1;
        elseif queue(2,i) < 2
            belowTwo = belowTwo + 1;
        elseif queue(2,i) < 3
            belowThree = belowThree + 1;
        end
    end


    airTemp = legsInAir;

    if belowOne + belowPointFive > 3
        velocity = Velocity;
        rotation = Rotation;
    end
    if belowPointFive > 0
        time = 500;
        pos = find(queue(2,:) < 0.5);
        for i = 1:length(pos)
            if liftable(airTemp, queue(1,pos(i)))
                airTemp(queue(1,pos(i))) = 1;
                movableLegs = movableLegs + 1;
                queue(2,pos(i)) = 500;
            else
                nerf = 1;
            end
        end
    end
    if belowOne > 0 && movableLegs < 3
        time = 500;
        pos = find(queue(2,:) < 1);
        for i = 1:length(pos)
            if liftable(airTemp, queue(1,pos(i)))
                airTemp(queue(1,pos(i))) = 1;
                movableLegs = movableLegs + 1;
                queue(2,pos(i)) = 500;
            end
        end
    end
    if belowTwo > 0 && movableLegs < 2
        time = 800;
        pos = find(queue(2,:) < 2);
        for i = 1:length(pos)
            if liftable(airTemp, queue(1,pos(i)))
                airTemp(queue(1,pos(i))) = 1;
                movableLegs = movableLegs + 1;
                queue(2,pos(i)) = 500;
            end
        end
    end

    if timespan < 6 && movableLegs < 1
        movableLegs = movableLegs + 1;
        time = max(500, 1000 - 500*(6-timespan)/3);
    end
    if timespan < 3 && movableLegs < 2 && highTime < 5
        movableLegs = movableLegs + 1;
        time = max(500, 1000 - 500*(3-timespan)/2);
    end
    if timespan < 2 && movableLegs < 3 && highTime < 3
        movableLegs = movableLegs + 1;
        time = max(500, 1000 - 500*(2-timespan));
    end
    
end


Velocity = velocity;
Rotation = rotation;


if mode == 3
    
    %absolute values are required.
    rotationTemp = abs(rotation);
    speed = sqrt(sum(velocity.^2));

    %During pure rotation.
    if speed == 0
        if rotationTemp(1) < 20
            movableLegs = 1;
        elseif rotationTemp(1) < 72
            movableLegs = 2;
        else
            movableLegs = 3;
        end

    %During pure walking.    
    elseif rotationTemp(1) == 0
        if speed < 5
            movableLegs = 1;
        elseif speed < 40
            movableLegs = 2;
        else
            movableLegs = 3;
        end

    %If both walking and rotating, better use all 3 legs ;)
    else
        movableLegs = 3;
    end

end
end