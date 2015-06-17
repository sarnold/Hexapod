function [trajectory] = makeLiftTrajectory(pos, goal, frequency, stepTime)
%Creates a trajectory based on the upper half of an ellips. Start position
%and end position is the needed parameters. Frequency and steptime allowes
%for the leg movement to be done in a specified timespan.


%Size of trajectory buffer
vSize = 50;

%just a constant to change when gone through the half ellips so it does not
%continue all the way around.
lastValue = 0;

%height of ellips
b = 30 - max(0,(50-pos(3)));
%Time for the step to take.
trajsample = stepTime;
%how frequently the step is supposed to be sampled.
sample = 1000/frequency;

%create the timespan with a sample rate of 1ms. Then choose appropriate
%samples from them according to constant "sample".
t = linspace(0,pi,trajsample);

%vector from start of ellipse to end of ellipse
moveVector = goal - pos;

%Width of the ellipse
a = sqrt(sum(moveVector(1:2).^2))/2;

%buffer
z = zeros(1,vSize);
temp = zeros(1,vSize);

%procedure to generate the ellipse. First quater of ellipse is generated from
%the startin position, second quater form the goal position. When the half
%ellipse is done put in the endvalue and then just zeroes in the rest of
%the buffer.
for i = 1:vSize
    
    %generating last value and the zeros
    if i*sample > trajsample
        %last value
        if lastValue == 0
            temp(i-1) = a - a*cos(pi);
            z(i-1) = goal(3) - b*sin(pi); %quickfix, changed pos to goal for hight alteration to work.
            lastValue = 1;
        end
        %zeros
        temp(i) = 0;
        z(i) = 0;
    
    %generating the ellipse
    else
        %First quater of ellipse
        if t(i*sample) <= pi/2
            temp(i) = a - a*cos(t(i*sample));
            z(i) = pos(3) - b*sin(t(i*sample));
        %Second quater of ellipse    
        else
            temp(i) = a - a*cos(t(i*sample));
            z(i) = goal(3) - (b + moveVector(3))*sin(t(i*sample));
        end
    end
end
    
%Project the ellipse x-axis on the movevector in the inital positions
%z-plane.
x = pos(1) + temp/max(temp)*moveVector(1);
y = pos(2) + temp/max(temp)*moveVector(2);

trajectory = [x;y;z];

end