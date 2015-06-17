%% SimMechanics Contact Forces Library
%
% <html>
% <span style="font-family:Arial">
% <span style="font-size:10pt">
% <tr><b><u>2D Collision Examples (Basic)</u></b><br>
% <tr>1.  Ball on Infinite Plane: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_01_Ball_Infinite_Plane;">Model</a>, <a href="matlab:web('Collision_01_Ball_Infinite_Plane_Anim.html');">Animation</a><br>
% <tr>2.  Disk on Finite Plane (fixed): <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_02_Disk_Finite_Plane_Fixed;">Model</a>, <a href="matlab:web('Collision_02_Disk_Finite_Plane_Fixed_Anim.html');">Animation</a><br>
% <tr>3.  Disk on Finite Plane (spin): <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_03_Disk_Finite_Plane_Spin;">Model</a>, <a href="matlab:web('Collision_03_Disk_Finite_Plane_Spin_Anim.html');">Animation</a><br>
% <tr>4.  Disks in Box: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_04_Disks_in_Box;">Model</a>, Animation (<a href="matlab:web('Collision_04_Disks_In_Box_Anim.html');">No Friction</a>, <a href="matlab:web('Collision_04_Disks_In_Box_Friction_Anim.html');">With Friction</a>)<br>
% <tr>5.  Disk in Ring: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_05_Disk_in_Ring;">Model</a>, Animation (<a href="matlab:web('Collision_05_Disk_In_Ring_Anim.html');">No Friction</a>, <a href="matlab:web('Collision_05_Disk_In_Ring_Friction_Anim.html');">With Friction</a>)<br>
% <tr>6.  Catapult: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_06_Catapult;">Model</a>, <a href="matlab:web('Collision_06_Catapult_Friction_Anim.html');">Animation</a><br>
% <tr>7.  Ball and Floating Beam: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_07_Ball_Finite_Plane_Float;">Model</a>, <a href="matlab:web('Collision_07_Ball_Finite_Plane_Float_Anim.html');">Animation</a><br>
% <br>
% <tr><b><u>2D Friction Examples (Basic)</u></b><br>
% <tr>1.  Box on Ramp (Constraint): <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_01_Box_on_Ramp_Constraint;">Model</a>, <a href="matlab:web('Friction_01_Box_on_Ramp_Constraint_Anim.html');">Animation</a><br>
% <tr>2.  Box on Ramp : <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_02_Box_on_Ramp;">Model</a>, <a href="matlab:web('Friction_02_Box_on_Ramp_Anim.html');">Animation</a><br>
% <tr>3.  Double Pendulum (Constraint): <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_03_Double_Pendulum_Constraint;">Model</a>, <a href="matlab:web('Friction_03_Double_Pendulum_Constraint_Anim.html');">Animation</a><br>
% <tr>4.  Disk Rolling on Ramp: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_04_Disk_Rolling_on_Ramp;">Model</a>, <a href="matlab:web('Friction_04_Disk_Rolling_on_Ramp_Anim.html');">Animation</a><br>
% <tr>5.  Beam on Wheel: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_05_Beam_on_Wheel;">Model</a>, <a href="matlab:web('Friction_05_Beam_on_Wheel_Anim.html');">Animation</a><br>
% <tr>6.  Disk on Disk: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_06_Disk_on_Disk;">Model</a>, <a href="matlab:web('Friction_06_Disk_on_Disk_Anim.html');">Animation</a><br>
% <tr>7.  Floating Disks: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_07_Floating_Disks;">Model</a>, <a href="matlab:web('Friction_07_Floating_Disks_Anim.html');">Animation</a><br>
% <tr>8.  Disks and Ring: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_08_Disks_and_Ring;">Model</a>, <a href="matlab:web('Friction_08_Disks_and_Ring_Anim.html');">Animation</a><br>
% <tr>9.  Ring on Disk: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Friction']);Friction_09_Ring_on_Disk_Float;">Model</a>, <a href="matlab:web('Friction_09_Ring_on_Disk_Float_Anim.html');">Animation</a><br>
% <br>
% <tr><b><u>2D Examples (Applications)</u></b><br>
% <tr>1.  Cam Follower: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Cam_Follower']);Cam_Follower;">Model</a>, <a href="matlab:web('Cam_Follower_Anim.html');">Animation</a>, <a href="matlab:web('Cam_Follower_Contact.html');">Force Description</a><br>
% <tr>2.  Geneva Drive: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Geneva_Drive']);Geneva_Drive;">Model</a>, <a href="matlab:web('Geneva_Drive_Anim.html');">Animation</a>, <a href="matlab:web('Geneva_Drive_Contact_Forces.html');">Force Description</a><br>
% <tr>3.  Spinning Boxes: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Spinning_Boxes']);Spinning_Boxes;">Model</a>, <a href="matlab:web('Spinning_Boxes_Anim.html');">Animation</a>, <a href="matlab:web('Box_to_Box_Contact_Forces.html');">Force Description</a><br>
% <br>
% <tr><b><u>SimMechanics Contact Forces Library </u></b><br>
% <tr>1.  <a href="matlab:web('Contact_Forces_Library_Use.html');">Using the Library</a><br>
% <tr>2.  <a href="matlab:cd([CFR_HomeDir '\Libraries']);Contact_Forces_Lib;">Library</a><br>
% <tr>3.  Forces: <a href="matlab:web('Force_Laws.html');">Laws</a><br>
% <tr>....a. Circle-to-Circle Force: <a href="matlab:web('Circle_to_Circle_Contact.html');">Description</a>, <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_04_Disks_in_Box;">Example (Disks in Box)</a><br>
% <tr>....b. Circle-to-Finite Line Force: <a href="matlab:web('Circle_to_Finite_Line_Contact.html');">Description</a>, <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_03_Disk_Finite_Plane_Spin;">Example (Ball on Finite Plane (spin))</a><br>
% <tr>....c. Circle-to-Ring Force: <a href="matlab:web('Circle_to_Ring_Contact.html');">Description</a>; Examples: <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple\Collision']);Collision_05_Disk_in_Ring;"> Disk in Ring</a>, <a href="matlab:cd([CFR_HomeDir '\Examples\2D\Simple']);Collision_06_Catapult;">Catapult</a><br>
% <tr>4.  Friction Force: <a href="matlab:web('Friction_Laws.html');">Laws</a><br>
% </style>
% </style>
% </html>
% 
% Copyright 2014 The MathWorks(TM), Inc.

