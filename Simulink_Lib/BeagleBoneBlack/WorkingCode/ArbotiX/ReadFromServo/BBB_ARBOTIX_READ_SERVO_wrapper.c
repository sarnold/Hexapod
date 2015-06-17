

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
void BBB_ARBOTIX_READ_SERVO_Outputs_wrapper(const uint8_T *portNbr,
			const uint8_T *id,
			const uint8_T *nbrOfServo,
			const uint8_T *nbrBytes,
			const uint8_T *reg,
			real_T *debug,
			uint16_T *dataOut,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
if(xD[0]==1){
    // Run Only on Target - BeagleBoneBlack */
# ifndef MATLAB_MEX_FILE
    
    unsigned char txBuffer[30],rxBuffer[100];
    
    struct termios serial;
    //Clear txBuffer
    for(int i=0;i<30;i++){
        txBuffer[i]=0;
    }
    
    //Setup correct number of bytes in return message
    //Get config of serial port store in serial
    if (tcgetattr(arbot_fd, &serial) < 0) {
          perror("Getting configuration");
          debug[0]=43;
    }
    //2 bytes are for the header
    serial.c_cc[VMIN] = 2+nbrOfServo[0]*nbrBytes[0];
    //TCSANOW the change occurs immediately.
    //TCSAFLUSH The change occurs after all output written to the file 
    // descriptor has been transmitted, and all input so far received 
    // but not read is discarded before the change is made.
    
    tcsetattr(arbot_fd, TCSAFLUSH, &serial); // Apply configuration
    
    
    
    //Output
    int bytesToSend=6+nbrOfServo[0];
    txBuffer[0]=0xFF;
    txBuffer[1]=0x04;//Instruction
    txBuffer[2]=bytesToSend;
    txBuffer[3]=reg[0];//Register
    txBuffer[4]=nbrBytes[0];//Number of bytes to each servo
    txBuffer[5]=nbrOfServo[0];//Number of servo to write to

    for(int i=0;i<nbrOfServo[0];i++){
            txBuffer[6+i]=id[i];
    }
    
    
    //Sending data
    int wcount = write(arbot_fd, txBuffer, bytesToSend);
    if (wcount < 0) {
        debug[0]=1;
    }
    else {
        debug[1]=wcount;
    }
    
     //Read return of data
    int rBytes=read(arbot_fd, rxBuffer, 2+nbrOfServo[0]*nbrBytes[0]);
    debug[2]=rBytes;
    
    if(rxBuffer[0]== 255){
     // process messages coming from Arbotix
        for(int i=0;i<nbrOfServo[0];i++){
            //Low byte on oddnumber high byte on even number
            dataOut[i]=(rxBuffer[3+2*i]<<8)|rxBuffer[2+2*i];
        }
    }
    else{
        debug[1]=42;
    }
     
//     debug[0]=runed;
//     if(runed == 900){   
//      close(arbot_fd);
//      debug[4]=4;
//     }
# endif
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
void BBB_ARBOTIX_READ_SERVO_Update_wrapper(const uint8_T *portNbr,
			const uint8_T *id,
			const uint8_T *nbrOfServo,
			const uint8_T *nbrBytes,
			const uint8_T *reg,
			const real_T *debug,
			const uint16_T *dataOut,
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

            serial.c_cc[VMIN] = 8;
            serial.c_cc[VTIME] = 0;

            
            fcntl(arbot_fd, F_SETFL, 0);//Turn off O_NDELAY
            // http://linux.die.net/man/3/termios
            serial.c_cc[VMIN] = 8;
            //Timeout in deciseconds for noncanonical read (TIME).
            serial.c_cc[VTIME] = 0;
            
            
            
            
            serial.c_cflag = B115200 | CS8 | CREAD| CLOCAL;

            tcsetattr(arbot_fd, TCSANOW, &serial); // Apply configuration


    # endif
    xD[0]=1;
    //For model terminate
    //close(arbot_fd);
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
