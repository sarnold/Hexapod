%Variables for revolute joints inside simmechanics
spring_stiff=0.001;%Nm/deg
damping_coeff=0.001;%Nm/(deg*sec)


%Contact force parameters for ball on plane cont
zinit=0.08;
sprad=0.01;
fvel=1e-2;


%% PID parameters for the servos

D = -0.18253;
I = -0.001736;
N = 33.234;
P = 4.1814;
satvel = 336.88;