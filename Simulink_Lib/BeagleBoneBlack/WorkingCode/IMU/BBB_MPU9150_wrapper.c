

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/* Include only when running on target hardware */
# ifndef MATLAB_MEX_FILE
	#include <unistd.h>
	#include <linux/i2c-dev.h>
	#include <errno.h>
	#include <sys/ioctl.h>
# else

	#include <mex.h>
	#include <simstruc.h>

# endif


#define I2C_DEVID  0x68;   //MPU9150 default adress      

// Global variables
int i2c_imu_fd;
int deviceI2CAddress = I2C_DEVID;
int accRange;
int gyroRange;
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
#define y_width 1
/*
 * Create external references here.  
 *
 */
/* %%%-SFUNWIZ_wrapper_externs_Changes_BEGIN --- EDIT HERE TO _END */
/* extern double func(double a); */
/* %%%-SFUNWIZ_wrapper_externs_Changes_END --- EDIT HERE TO _BEGIN */

/*
 * Output functions
 *
 */
void BBB_MPU9150_Outputs_wrapper(const int8_T *accSens,
			const int8_T *gyroSens,
			real_T *acc,
			real_T *gyr,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
if(xD[0]==1){
    // Run Only on Target - BeagleBoneBlack */
    # ifndef MATLAB_MEX_FILE
    
            //page 28 Registermap Byte skift 2^11=2048 2^14=1683
            const double accScale[] = {16384,8192,4096,2048};
            //page 30 Registermap Byte skift 131/2 131/4 131/8
            const double gyroScale[] = {131,65.5,32.8,16.4};

            double conVert(char highByte,char lowByte,double scaleFactor){
                    int temp=(((int) highByte) << 8) | lowByte;

                    //Check if number is negative
                    if((temp) & (1 << 15)){
                        temp=-((temp ^ 0xFFFF)+1);
                    }
                    return (double) temp/scaleFactor;
            }


            //Read data new output panel
            //Code for reading register 59
            char rxBuff[20];
            rxBuff[0]=59;//address start
            write(i2c_imu_fd,rxBuff,1);

            int nbr=read(i2c_imu_fd,rxBuff,14);//Läser 3 
            /* Using SMBus commands */
            //int res = i2c_smbus_read_word_data(i2c_imu_fd, 107);//test reg


            acc[0]=conVert(rxBuff[0],rxBuff[1],accScale[accRange]);
            acc[1]=conVert(rxBuff[2],rxBuff[3],accScale[accRange]);
            acc[2]=conVert(rxBuff[4],rxBuff[5],accScale[accRange]);

            gyr[0]=conVert(rxBuff[8],rxBuff[9],gyroScale[gyroRange]);
            gyr[1]=conVert(rxBuff[10],rxBuff[11],gyroScale[gyroRange]);
            gyr[2]=conVert(rxBuff[12],rxBuff[13],gyroScale[gyroRange]);



        # else
    # endif
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
void BBB_MPU9150_Update_wrapper(const int8_T *accSens,
			const int8_T *gyroSens,
			const real_T *acc,
			const real_T *gyr,
			real_T *xD)
{
  /* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
if (xD[0]!=1) {
    # ifndef MATLAB_MEX_FILE
        //Sensitivity of accelerometer 2g,4g,8g,16g
        //Sensitivity of gyro 250,500,1000,2000 degree/s
        const char sens[]={0,8,16,24};
        
        accRange=accSens[0]-1;
        gyroRange=gyroSens[0]-1;
        
 
        i2c_imu_fd  = open("/dev/i2c-1", O_RDWR);
 
        if (i2c_imu_fd  < 0) {
                printf("\nError opening file: %s\n","/dev/i2c-1");
        }
        if (ioctl(i2c_imu_fd, I2C_SLAVE, deviceI2CAddress) < 0) {
                printf("\nError ioctl");
        }

        //Setup

        //accelerometer sensisitivity
        char txBuff[2];
        txBuff[0]=107;
        txBuff[1]=1;
        
        write(i2c_imu_fd, txBuff, 2);
       
        //gyro sensisitivity
        txBuff[0]=27;
        txBuff[1]=sens[gyroRange];
        write(i2c_imu_fd, txBuff, 2);
        
        //accelerometer sensisitivity
        txBuff[0]=28;
        txBuff[1]=sens[accRange];
        write(i2c_imu_fd, txBuff, 2);

    # endif
    xD[0]=1;
    
    //Code for model terminate
    //close(i2c_imu_fd);
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
