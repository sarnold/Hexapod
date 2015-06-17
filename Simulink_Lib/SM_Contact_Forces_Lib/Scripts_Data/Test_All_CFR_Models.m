% Copyright 2014 The MathWorks, Inc.

clear CFR_Res

cd([CFR_HomeDir '/Scripts_Data']);

mdlnames = {'Collision_01_Ball_Infinite_Plane',...
    'Collision_02_Disk_Finite_Plane_Fixed',...
    'Collision_03_Disk_Finite_Plane_Spin',...
    'Collision_04_Disks_in_Box',...
    'Collision_05_Disk_in_Ring',...
    'Collision_06_Catapult',...
    'Collision_07_Ball_Finite_Plane_Float',...
    'Collision_08_Compare_Forces',...
    'Friction_01_Box_on_Ramp_Constraint',...
    'Friction_02_Box_on_Ramp',...
    'Friction_03_Double_Pendulum_Constraint',...
    'Friction_04_Disk_Rolling_on_Ramp',...
    'Friction_05_Beam_on_Wheel',...
    'Friction_06_Disk_on_Disk',...
    'Friction_07_Floating_Disks',...
    'Friction_08_Disks_and_Ring',...
    'Friction_09_Ring_on_Disk_Float',...
    'Cam_Follower',...
    'Geneva_Drive',...
    'Spinning_Boxes'};

CFR_Res{1,1} = '#';
CFR_Res{1,2} = 'Model';
CFR_Res{1,3} = 'Stop Time';
CFR_Res{1,4} = '# Steps';
CFR_Res{1,5} = 'Sim Time';
CFR_Res{1,6} = '# Steps';
CFR_Res{1,7} = 'Sim Time';
CFR_Res{1,8} = '# Steps';
CFR_Res{1,9} = 'Sim Time';
CFR_Res{1,10} = '# Steps';
CFR_Res{1,11} = 'Sim Time';

for mdl_i = 1:length(mdlnames)
    mdl = char(mdlnames{mdl_i});
    open_system(mdl);
    disp(['TESTING ' mdl ' ...']);
    CF_bpth=find_system(bdroot,'RegExp','on','LookUnderMasks','on','force_law','.*');
    CR_bpth=find_system(bdroot,'RegExp','on','LookUnderMasks','on','friction_law','.*');
    
    if(~isempty(CF_bpth))
        for i=1:length(CF_bpth)
            set_param(char(CF_bpth(i)),'force_law','Linear');
        end
    end
    
    if(~isempty(CR_bpth))
        for i=1:length(CR_bpth)
            set_param(char(CR_bpth(i)),'friction_law','None');
        end
    end    
    sim(mdl);
    CFR_Res{mdl_i+1,1} = mdl_i;
    CFR_Res{mdl_i+1,2} = mdl;
    CFR_Res{mdl_i+1,3} = sprintf('%5.2f',str2double(get_param(bdroot,'StopTime')));
    CFR_Res{mdl_i+1,4} = num2str(length(tout));
    CFR_Res{mdl_i+1,5} = sprintf('%5.3f',Elapsed_Sim_Time);
    
    if(~isempty(CF_bpth))
        for i=1:length(CF_bpth)
            set_param(char(CF_bpth(i)),'force_law','Linear');
        end
    end
    
    if(~isempty(CR_bpth))
        for i=1:length(CR_bpth)
            set_param(char(CR_bpth(i)),'friction_law','Stick-Slip Continuous');
        end
    end
    sim(mdl);
    CFR_Res{mdl_i+1,6} = num2str(length(tout));
    CFR_Res{mdl_i+1,7} = sprintf('%5.3f',Elapsed_Sim_Time);

    if(~isempty(CF_bpth))
        for i=1:length(CF_bpth)
            set_param(char(CF_bpth(i)),'force_law','Nonlinear');
        end
    end
    
    if(~isempty(CR_bpth))
        for i=1:length(CR_bpth)
            set_param(char(CR_bpth(i)),'friction_law','None');
        end
    end
    sim(mdl);
    CFR_Res{mdl_i+1,8} = num2str(length(tout));
    CFR_Res{mdl_i+1,9} = sprintf('%5.3f',Elapsed_Sim_Time);

    if(~isempty(CF_bpth))
        for i=1:length(CF_bpth)
            set_param(char(CF_bpth(i)),'force_law','Nonlinear');
        end
    end
    if(~isempty(CR_bpth))
        for i=1:length(CR_bpth)
            set_param(char(CR_bpth(i)),'friction_law','Stick-Slip Continuous');
        end
    end
    sim(mdl);
    CFR_Res{mdl_i+1,10} = num2str(length(tout));
    CFR_Res{mdl_i+1,11} = sprintf('%5.3f',Elapsed_Sim_Time);

    bdclose(mdl);
    disp(['FINISHED TESTING ' mdl]);
end

xlswrite('CFR_Results',{'Contact Forces Tests'},'Results','B1');
xlswrite('CFR_Results',{version},'Results','C1');
xlswrite('CFR_Results',{datestr(now)},'Results','F1');
xlswrite('CFR_Results',CFR_Res,'Results','A3')
