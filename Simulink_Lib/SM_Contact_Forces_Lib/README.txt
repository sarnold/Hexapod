SimMechanics Contact Forces Library
Copyright 2014 The MathWorks, Inc.

This library contains contact force models for use with SimMechanics Second Generation.
They can be used for intermittent contact (parts bouncing off each other)
and persistent contact (parts resting on each other).

To use them:
   1. Identify the parts in your system that will hit each other during simulation

   2. Figure out which edges will touch.  
      The contact models provided allow you to model contact between combinations
      of connected straight lines and circular arcs.

   3. Add reference frames for the lines and arcs that will touch.

      For straight lines, the reference frame must be placed along the normal 
      to the midpoint of the line with the x-axis oriented normal to the line 
      and the y-axis along the line.

      For circular arcs, the reference frame must be at the center of the circle
      that is defined by the circular arc.
      
   4. Add the correct contact force model between the two frames.

See the examples to understand how they are used.

Recommendations:
   1. Start with stiffness of 1e4 and damping of 1e2 and adjust from there.
   2. Use solver ode15s, Relative Tolerance = 1e-4, Absolute Tolerance = 1e-5
       and set the maximum step size to 1e-2.
   3. If you get unexpected behavior (parts flying through one another, 
       system gaining energy) your tolerances are not small enough.
       Reduce tolerances by a factor of 10 and max step size by a factor of 10
       until you get expected behavior.  Reducing stiffness and increasing damping
       can also help.

#########  Release History  #########  
v 2.0 (R2014a)  September 2014	Friction model added
                1. Added optional friction model (Stick-Slip Continuous)
		   to Circle to Circle, Circle to Finite Line, Circle to Ring
                2. Added all Friction_* examples 
                3. Added Spinning Boxes example 
                   Shows box-to-box contact force
                4. Fixed callback commands, all contact force blocks
		   Set variant in Initialization commands instead of mask callbacks
                5. Fixed Circle to Finite Line, Circle to Finite Line Enabled
                   Force on line was applied in wrong reference frame

v 1.0 (R2014a)  August 2014     Initial release.
		Circle-Circle (Enabled), Circle-Line (Enabled), Circle-Ring
		7 Simple, Cam Follower, Geneva Drive. Mini Golf compatible


