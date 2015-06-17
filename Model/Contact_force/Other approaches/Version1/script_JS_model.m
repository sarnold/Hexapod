%warning off;

%%% Initialization for mechanism topology
tsim = 1e-4;
L1 = 0.25;
L2 = 0.125;
rcyl = 0.005;
eps = 1e-5;
psi = 0.2;
rho = 500; % adjustment of arm mass
beta = 60; %initial angle of arm
Ts = 1e-2;

khs = 1e4; % hard stop stiffness
chs = 15; % hard stop damping

%%% Initial simulation por position dtermination
zinit = 5;
sim('spindel_ben_contact.slx');
zinit = abs(pos_z.signals.values(1,1)); %calculate z-coord initial

%%% Valid simulation
tsim = 2;
sim('spindel_ben_contact.slx');
tid = Fcontact.time(:,1);
Fcx = Fcontact.signals.values(:,1);
Fcy = Fcontact.signals.values(:,2);
Fcz = Fcontact.signals.values(:,3);

%%% Graphical representation of contact forces
hold on;
plot(tid, 10*Fcy, 'Color', 'b', 'LineWidth', 2);
plot(tid, Fcz, 'Color', 'g', 'LineWidth', 2);
grid on;
xlim([0.87 0.89]);
xlabel('time[sec]');
ylabel('Force[N]');
legend('10*Fcy[N]', 'Fcz[N]', 'Location', 'NorthEast');




