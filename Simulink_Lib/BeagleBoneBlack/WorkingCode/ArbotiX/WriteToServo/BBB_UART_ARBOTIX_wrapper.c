

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
/* Include only when running on target hardware */
# ifndef MATLAB_MEX_FILE
	#define _BSD_SOURCE 
	#include <unistd.h>
	#include <stdio.h>
	#include <string.h>
	#include <fcntl.h>
	#include <termios.h>
# else

	#include <mex.h>
	#include <simstruc.h>

# endif

// Global variables
int arbot_fd;
/* %%%-SFUNWIZ_wrapper_includes_Changes_END --- EDIT HERE TO _BEGIN */
#define u_width 1
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
void BBB_UART_ARBOTIX_Outputs_wrapper(const uint8_T *portNbr,
			const uint8_T *data,
			const uint8_T *nbrBytes,
			real_T *debug,
			real_T *data_out,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
//This function reads the next avalibel message from the commander
// Message are sent at a rate of 30 Hz

if(xD[0]==1){
    // Run Only on Target - BeagleBoneBlack */
# ifndef MATLAB_MEX_FILE
    
    unsigned char txBuffer[255];
    //Clear txBuffer
    for(int i=0;i<255;i++){
        txBuffer[i]=0;
    }
    
    int nbr=nbrBytes[0];
    
    //Output
    int bytesToSend=5+18*nbr;
    txBuffer[0]=0xFF;
    txBuffer[1]=0x03;//Instruction
    txBuffer[2]=bytesToSend;
    txBuffer[3]=30;//Register
    txBuffer[4]=nbr;//Amount to each servo
    
    
    for(int i=0;i<bytesToSend-5;i++){
            txBuffer[i+5]=data[i];
    }
    
    
    //Sending data
    int wcount = write(arbot_fd, txBuffer, bytesToSend);
    if (wcount < 0) {
        debug[0]=1;
    }
    else {
        debug[1]=wcount;
    }
    
# endif
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
void BBB_UART_ARBOTIX_Update_wrapper(const uint8_T *portNbr,
			const uint8_T *data,
			const uint8_T *nbrBytes,
			const real_T *debug,
			const real_T *data_out,
			real_T *xD)
{
  /* %%%-SFUNWIZ_wrapper_Update_Changes_BEGIN --- EDIT HERE TO _END */
if (xD[0]!=1) {
    // Run Only on Target - BeagleBoneBlack */
    # ifndef MATLAB_MEX_FILE

        struct termios serial;

        //SE http://beaglebone.cameon.net/home/serial-ports-uart
        //UART0 Beaglebone black only
        //UART1 RX P9_26 TX P9_24 /dev/ttyO1
        //UART2 RX P9_22 TX P9_21 /dev/ttyO2
        //UART3 RX       TX P9_42 /dev/ttyO3 TX ONLY
        //UART4 RX P9_11 TX P9_13 /dev/ttyO4
        //UART5 RX P8_28 TX P8_24 /dev/ttyO5
        //

        //Open serial port with option
        //O_RDWR Open for reading and writing
        //O_NOCTTY Do not assign controlling terminal.
        //O_NDELAY The open will return without waiting for the device to
        // be ready or available; subsequent behavior of the device is device specific
        switch(portNbr[0]){
            case 1 :
                   arbot_fd = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NDELAY);
            break;
            case 2 :
                   arbot_fd = open("/dev/ttyO2", O_RDWR | O_NOCTTY | O_NDELAY);
            break;
            case 3 :
                   arbot_fd = open("/dev/ttyO4", O_RDWR | O_NOCTTY | O_NDELAY);
            break;
            case 4 :
                   arbot_fd = open("/dev/ttyO5", O_RDWR | O_NOCTTY | O_NDELAY);
            break;
        }

        //Get config of serial port store in serial
        if (tcgetattr(arbot_fd, &serial) < 0) {
            perror("Getting configuration");
        }

         // Set up Serial Configuration
            serial.c_iflag = 0;
            serial.c_oflag = 0;
            serial.c_lflag =0;
            serial.c_cflag = 0;

            serial.c_cc[VMIN] = 0;
            serial.c_cc[VTIME] = 0;


            serial.c_cflag = B115200 | CS8 | CREAD| CLOCAL;

            tcsetattr(arbot_fd, TCSANOW, &serial); // Apply configuration

        //For model terminate
        //close(arbot_fd);

    # endif
    xD[0]=1;
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
