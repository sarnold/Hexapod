

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
	#include <sys/ioctl.h>
# else

	#include <mex.h>
	#include <simstruc.h>

# endif

// Global variables
int xbee_fd;
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
void BBB_UART_XBEE_Outputs_wrapper(const int8_T *portNbr,
			uint8_T *data,
			int8_T *walkV,
			int8_T *walkH,
			int8_T *lookV,
			int8_T *lookH,
			uint8_T *buttons,
			uint16_T *debug,
			const real_T *xD)
{
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_BEGIN --- EDIT HERE TO _END */
//This function reads the next avalibel message from the commander
// Message are sent at a rate of 30 Hz

if(xD[0]==1){
    // Run Only on Target - BeagleBoneBlack */
# ifndef MATLAB_MEX_FILE
    char startByte=0;
    char buffer[8];
    
    //Dessa två rader är nya
    int bytes_avaiable=0;
    ioctl(xbee_fd, FIONREAD, &bytes_avaiable);
    debug[0]=bytes_avaiable;
    if(bytes_avaiable>=8){
        read(xbee_fd, buffer, 8);
        //Empty the buffer
        for(int i=0;i<8;i++){
            data[i]=buffer[i];
        }
        if(buffer[0]== 255){
            /* process messages coming from Commander 
             *  format = 0xFF RIGHT_V RIGHT_H LEFT_V LEFT_H BUTTONS EXT CHECKSUM */
            lookV[0] = buffer[1]-128;
            lookH[0] = buffer[2]-128;
            walkV[0] = buffer[3]-128;
            walkH[0] = buffer[4]-128;
            buttons[0]= buffer[5];
        }
        else{
            debug[1]=42;
        }
    }
# endif
}
/* %%%-SFUNWIZ_wrapper_Outputs_Changes_END --- EDIT HERE TO _BEGIN */
}

/*
  * Updates function
  *
  */
void BBB_UART_XBEE_Update_wrapper(const int8_T *portNbr,
			const uint8_T *data,
			const int8_T *walkV,
			const int8_T *walkH,
			const int8_T *lookV,
			const int8_T *lookH,
			const uint8_T *buttons,
			const uint16_T *debug,
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
                   xbee_fd = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NDELAY);
            break;
            case 2 :
                   xbee_fd = open("/dev/ttyO2", O_RDWR | O_NOCTTY | O_NDELAY);
            break;
            case 3 :
                   xbee_fd = open("/dev/ttyO4", O_RDWR | O_NOCTTY | O_NDELAY);
            break;
            case 4 :
                   xbee_fd = open("/dev/ttyO5", O_RDWR | O_NOCTTY | O_NDELAY);
            break;
        }

        //Get config of serial port store in serial
        if (tcgetattr(xbee_fd, &serial) < 0) {
            perror("Getting configuration");
        }

        // Set up Serial Configuration
        serial.c_iflag = 0;
        serial.c_oflag = 0;
        //ICANON disable canonical mode
        //ECHO off Echo input characters
        //CHECK this byte
        serial.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);//Raw input
        serial.c_cflag = 0;


        fcntl(xbee_fd, F_SETFL, 0);//Turn of bit
        // http://linux.die.net/man/3/termios
        serial.c_cc[VMIN] = 8;
        //Timeout in deciseconds for noncanonical read (TIME).
        serial.c_cc[VTIME] = 0;


        //Set baudrate |8 databit | 1 stopbit Enable receiver
        serial.c_cflag = B38400 | CS8 | CREAD | CLOCAL;

        //TCSANOW the change occurs immediately.
        tcsetattr(xbee_fd, TCSANOW, &serial); // Apply configuration

        

    # endif
    xD[0]=1;
    
    //For model terminate
    //close(xbee_fd);
}
/* %%%-SFUNWIZ_wrapper_Update_Changes_END --- EDIT HERE TO _BEGIN */
}
