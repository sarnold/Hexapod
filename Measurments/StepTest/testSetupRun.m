id = 1;
%start and stop is in a range of 0-1023 bits = 0-300 degrees
%positive direction of motion is when the wheight will load the motion, in
%opposite direction it will help the motion.
startPos = 400;
stopPos = 810;
speed = 200;
%load is the weight in grams that hangs on the thread in circular motion
%load is the wheight in grams put in either the outer hole (o) or inner
%hole (i) in arm motion, weight of arm is 68g.
load = '0';
mode = 'random';

sim('TestSetup');


%head = [linspace(-400,-5,80)' ones(80,1)*startPos zeros(80,1)];
result = double(result);

%keep a copy of the raw data
resultcopy = result;

result(find(result(:,2) == 0),:) = [];

maxTorqueBin = result(length(result),3);
voltageBin = result(length(result),1);
voltage = voltageBin/10;
maxTorqueNm = (maxTorqueBin/1023)*1.5*(voltage/12);

result(length(result),:) = [];

for k = [1:1:length(result)]
    if (result(k,3) < 1024)
        result(k,3) = (result(k,3)/1023)*maxTorqueNm;
    elseif (result(k,3) > 1023)
        result(k,3) = -((result(k,3)-1024)/1023)*maxTorqueNm;
    end
end
           
%Plot the results of the step response
% result = [head; result];
step = result;
step(:,2) = stopPos;
figure(1);
subplot(2,1,1);
plot(result(:,1),result(:,2),'.',step(:,1),step(:,2),'-');
title('Step response');
xlabel('Time (ms)');
ylabel('Position (bit)');
subplot(2,1,2);
plot(result(:,1),result(:,3),'-');
title('Torque (negative = clockwise)');
xlabel('Time (ms)');
ylabel('Torque (Nm)');
figure(1)


%% Save data to file
mkdir(strcat(pwd, '\Results\step', int2str(startPos), 'to', int2str(stopPos), mode, 'Load', load, 'Speed', int2str(speed), 'Voltage', int2str(voltageBin)));
dataPath = strcat(pwd, '\Results\step', int2str(startPos), 'to', int2str(stopPos), mode, 'Load', load, 'Speed', int2str(speed), 'Voltage', int2str(voltageBin), '\data.m');
printData = [result(:,1:2) step(:,2)];
fileID = fopen(dataPath, 'wt');
dataName = strcat('step', int2str(startPos), 'to', int2str(stopPos), '=[');
fprintf(fileID, '%13s\n',dataName);
fprintf(fileID, '%6.0f %12.0f %18.0f\n', printData');
fprintf(fileID, '%2s','];');
fclose(fileID);
figurePath = strcat(pwd, '\Results\step', int2str(startPos), 'to', int2str(stopPos), mode, 'Load', load, 'Speed', int2str(speed), 'Voltage', int2str(voltageBin), '\plot');
savefig(figurePath);
save(strcat(pwd, '\Results\step', int2str(startPos), 'to', int2str(stopPos), mode, 'Load', load, 'Speed', int2str(speed), 'Voltage', int2str(voltageBin), '\workspace'));



