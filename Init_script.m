%Init script
%genpath adds all subfolders
%StartBB and StopBB can be use to start and stop model running on hardware


addpath(genpath([pwd '/Simulink_Lib']));
CFR_HomeDir = [pwd '/Simulink_Lib/SM_Contact_Forces_Lib'];%%To make exampels working
%web('Contact_Forces_Demo_Script.html');%Demo for 


%Load model files
addpath([pwd '/Model']);
addpath(genpath([pwd '/Model/CAD/Hexapod/Cad export']));
addpath([pwd '/Model/Contact_force']);

addpath([pwd '/Control']);
addpath([pwd '/Control/MatlabFunctions']);



%% Load custom data
load([pwd '/Simulink_Lib/Custom_buses.mat']);
simmechinit

%% Load simulink models
%Code generation model
%CodeGenerationSetup

%Simulation model
DevelopmentModel


%Model for measerment of execution profiling
%ExecutionTiming
%Run this line to produce a report of the execution timing
%report(executionProfile, 'Units', 'Seconds', 'ScaleFactor', '1', 'NumericFormat', '%0.3f');

%Used to compare simulation runing on target and simulation running on PC
%PILComparison



