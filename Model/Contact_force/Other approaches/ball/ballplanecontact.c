/* Ball Plane Contact
 * 
 * Janne Salomäki, 9.2.2015
 */ 

#define S_FUNCTION_NAME  	ballplanecontact
#define S_FUNCTION_LEVEL	2
#include "simstruc.h"
#include <math.h>
#define PAR(element)		(*mxGetPr(ssGetSFcnParam(S,element)))
#define U(element) 			(*uPtrs[element])

/* Parameters. */
#define xpla	 			PAR(0)	/* Plane length. */
#define ypla	 			PAR(1)	/* Plane width. */
#define zpla	 			PAR(2)	/* Plane thickness. */
#define rbal	 			PAR(3)	/* Ball radius. */
#define Kpen	 			PAR(4)	/* Penetration spring constant. */
#define Dpen	 			PAR(5)	/* Penetration damping constant. */
#define mustat	 			PAR(6)	/* Static friction constant. */
#define vthr	 			PAR(7)	/* Friction threshold speed . */

/* Inputs. */
#define vx                  U(0)    /* Ball speed x. */
#define vy                  U(1)	/* Ball speed y. */
#define pz                  U(2)	/* Ball position z. */
#define vz                  U(3)    /* Ball speed z. */
#define wx                  U(4)	/* Ball rotation speed x. */
#define wy                  U(5)	/* Ball rotation speed y. */


/* Continuous states and their derivatives. */
#define xpos                x[0]	/* Ball position in x-direction. */
#define ypos                x[1]	/* Ball position in y-direction. */

#define dxpos               dx[0]	/* Derivative of xpos. */
#define dypos               dx[1]   /* Derivative of ypos. */

/* Other definitions. */
#define PI 					3.14159265358979

/* Initialization. */
static void mdlInitializeSizes(SimStruct *S) {
    ssSetNumSFcnParams(S, 8);  
    if(ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) return;
    ssSetNumContStates(S, 2);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;
    ssSetInputPortWidth(S, 0, 6);
    ssSetInputPortDirectFeedThrough(S, 0, 6);

    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 7);

    ssSetNumSampleTimes(S, 1);
	ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S) {
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

#define MDL_INITIALIZE_CONDITIONS  
#if defined(MDL_INITIALIZE_CONDITIONS)
static void mdlInitializeConditions(SimStruct *S) {
	real_T *x0 = ssGetContStates(S);
    x0[0] = 0;      
    x0[1] = 0;         
}
#endif /* MDL_INITIALIZE_CONDITIONS */

static void mdlOutputs(SimStruct *S, int_T tid) {
	real_T              *y    = ssGetOutputPortRealSignal(S,0);
	real_T              *x    = ssGetContStates(S);	
    InputRealPtrsType   uPtrs = ssGetInputPortRealSignalPtrs(S,0);	        
    real_T              cgap, Fz;
    real_T              vxlin, vylin, vxc, vyc;
    real_T              mux, muy, Ffx, Ffy;
    real_T              Tx, Ty;
    
    /* Support force parameters. */    
    cgap = zpla/2+rbal;
        
    /* Support force model. */
    if (pz<cgap && fabs(xpos)<xpla/2 && fabs(ypos)<ypla/2)
        Fz = -Kpen*(pz-cgap)-Dpen*vz;
    else
        Fz = 0;
        
    /* Circumferential speed.*/
    vxc = -rbal*wy;
    vyc = -rbal*wx;
    
    vxlin = -vxc-vx;
    vylin = vyc-vy;
    
    /* Friction force X. */
    if (fabs(vxlin) <= vthr)
        mux = mustat * vxlin/vthr;
    else if(vxlin > vthr)
        mux = mustat;
    else
        mux = -mustat;    
    Ffx = mux*Fz;
    
    /* Friction force Y. */
    if (fabs(vylin) <= vthr)
        muy = mustat * vylin/vthr;
    else if(vylin > vthr)
        muy = mustat;
    else
        muy = -mustat;    
    Ffy = muy*Fz;
    
    /* Rolling torques. */
    Tx = rbal*Ffy;
    Ty = -rbal*Ffx;
    
    y[0] = Fz; 
	y[1] = Ffx;
    y[2] = Ffy; 
	y[3] = Tx;
    y[4] = Ty;
    y[5] = vx;
    y[6] = vy;
}

#define MDL_DERIVATIVES
#if defined(MDL_DERIVATIVES)
static void mdlDerivatives(SimStruct *S) {
	real_T              *dx   = ssGetdX(S);
    real_T              *x    = ssGetContStates(S);
    InputRealPtrsType   uPtrs = ssGetInputPortRealSignalPtrs(S,0);
    
    /* Derivatives. */
    dxpos = vx;
    dypos = vy;
    
}
#endif /* MDL_DERIVATIVES */

/* No termination needed, but we are required to have this routine. */
static void mdlTerminate(SimStruct *S)
{
}

#ifdef  MATLAB_MEX_FILE  
#include "simulink.c"    
#else
#include "cg_sfun.h"       
#endif
