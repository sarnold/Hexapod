

/*
 * Include Files
 *
 */
#if defined(MATLAB_MEX_FILE)
#include "tmwtypes.h"
#include "simstruc_types.h"
#else
#include "rtwtypes.h"
#endif

/* %%%-SFUNWIZ_wrapper_includes_Changes_BEGIN --- EDIT HERE TO _END */
#define M_PI 3.14159265358979323846264338327
/* Include only when running on target hardware */
# ifndef MATLAB_MEX_FILE
	//#define _BSD_SOURCE
	#include <stdio.h>
	#include <stdint.h>
	#include <stdlib.h>
	#include <string.h>
	#include <signal.h>
	#include <getopt.h>
	#include <errno.h>
 	#include "inv_mpu.h"
 	#include "inv_mpu.c"
        #include "inv_mpu_dmp_motion_driver.h"
        #include "inv_mpu_dmp_motion_driver.c"
        #include "linux_glue.h"
        #include "linux_glue.c"
 	#include "vector3d.h"
 	#include "vector3d.c"
	#include "quaternion.h"
	#include "quaternion.c"
        #include "mpu9150.h"
        #include "mpu9150.c"

# else
	#include <mex.h>
	#include <simstruc.h>
# endif
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
 
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void BBB_IMU_DMP_Outputs_wrapper(real_T *debug,
			real_T *angle,
			const real_T *xD,
			const int16_T  *acc_cal, const int_T  p_width0,
			const int16_T  *mag_cal, const int_T  p_width1)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
//MEX configured to use Microsoft Windows SDK 7.1 (C) for C language compilation.
if(xD[0]==1){
    // Run Only on Target - BeagleBoneBlack */
    # ifndef MATLAB_MEX_FILE

        mpudata_t mpu;
        memset(&mpu, 0, sizeof(mpudata_t));

        //Read and fuse angles
        if (mpu9150_read(&mpu) == 0) {
            angle[0]=(double)(mpu.fusedEuler[VEC3_X] * RAD_TO_DEGREE); 
            angle[1]=(double)(mpu.fusedEuler[VEC3_Y] * RAD_TO_DEGREE); 
            angle[2]=(double)(mpu.fusedEuler[VEC3_Z] * RAD_TO_DEGREE);
        }
        else{
                debug[0]=1;
        }
    # endif

}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
void BBB_IMU_DMP_Update_wrapper(const real_T *debug,
			const real_T *angle,
			real_T *xD,
			const int16_T  *acc_cal,  const int_T  p_width0,
			const int16_T  *mag_cal,  const int_T  p_width1)
{
  /* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
# ifndef MATLAB_MEX_FILE

//Use to set calebration values for acceleromenter and magnetometer
int set_cal(int mag)
{
	int i;
	char buff[32];
	long val[6];
	caldata_t cal;

	long acc_cal[6] = {-17716, 18368, -18318, 18370, -18576,20110};
	long mag_cal[6] = {-250,130,-161,202,-145,236};

    //Empty the buffer
	memset(buff, 0, sizeof(buff));
	
	for (int i = 0; i < 6; i++) {
        if (mag) 
	        	val[i] = mag_cal[i];
    	else 
		        val[i] = acc_cal[i];
	}

	cal.offset[0] = (short)((val[0] + val[1]) / 2);
	cal.offset[1] = (short)((val[2] + val[3]) / 2);
	cal.offset[2] = (short)((val[4] + val[5]) / 2);

	cal.range[0] = (short)(val[1] - cal.offset[0]);
	cal.range[1] = (short)(val[3] - cal.offset[1]);
	cal.range[2] = (short)(val[5] - cal.offset[2]);
	
	if (mag) 
		mpu9150_set_mag_cal(&cal);
	else 
		mpu9150_set_accel_cal(&cal);

	return 0;
}


if (xD[0]!=1) {
    // Run Only on Target - BeagleBoneBlack */

        int i2c_bus =1;
        int sample_rate = 10;
        int yaw_mix_factor = 4;
        int verbose = 0;

        //MIN_SAMPLE_RATE 2 MAX_SAMPLE_RATE 100 se mpu9150.h
        sample_rate = 50;

        //yaw mix factor [0 100]

        //Effect of mag yaw on fused yaw data.
        // 0 = gyro only
        //  1 = mag only\n");
        // > 1 scaled mag adjustment of gyro data
        yaw_mix_factor=4;

        //verbose = 1; use to set debug on
        verbose=0;
        mpu9150_set_debug(verbose);

        if (mpu9150_init(i2c_bus, sample_rate, yaw_mix_factor))
        
        //Apply calebration values for gyro and accelerometer
        set_cal(0);//acc cal
        set_cal(1);// mag cal
      
        xD[0]=1;
}


# endif
//If runing in simulation
if (xD[0]!=1) {
    xD[0]=1;
}
//Terminate function
//	mpu9150_exit();
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
