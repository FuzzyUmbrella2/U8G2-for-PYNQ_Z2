#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xstatus.h"
#include "sleep.h"

#include "Defines_example.h"
#include "SH1106_Screen.h"

int Counter = 0;
XScuGic intCtrl;	// the interrupt controller
XTmrCtr timer;		// the timer

void Timer_Handler(void *userParam, u8 TmrCtrNumber)
{
	if (Counter > 1000)
	{
		Counter = 0;
	}

	// Print the input voltage
	// Turn float data into a string
	char buffer[32];
	sprintf(buffer, "%i", Counter);

	// update screen
	printCentreX(0,"Counter =");
	txtWthFrameCentreX(15, buffer);
}

void initInterrupt()
{
    // Get the config of the interrupt controller
    XScuGic_Config *IntcConfig = XScuGic_LookupConfig(GicID);
    if (NULL == IntcConfig) {
    	printf("\n\r XScuGic_LookupConfig() failed\n");
    }

    // initialize the initerrupt controller
    int Status = XScuGic_CfgInitialize(&intCtrl, IntcConfig,IntcConfig->CpuBaseAddress);
    if (Status != XST_SUCCESS) {
    	printf("\n\r XScuGic_CfgInitialize() failed\n");
    }


	// initialize the timer
    Status =  XTmrCtr_Initialize(&timer, TImerID);
    if (Status != XST_SUCCESS) {
    	printf("Could not initialize timer \n\r");
    }
    // link the timer and the interrupt handler
    XTmrCtr_SetHandler(&timer, (XTmrCtr_Handler)Timer_Handler, (void*) 0x12345678);

    // set prioroty to place 160 (aka 0xA0) and the trigger to risign edge (aka 0x3)
    XScuGic_SetPriorityTriggerType(&intCtrl, TimerIntrID, 0xA0, 0x3);		// priority of 160

    // connect the interrupt controller to the timer
    Status = XScuGic_Connect(&intCtrl,  TimerIntrID,(Xil_InterruptHandler)XTmrCtr_InterruptHandler,&timer);
    if (Status != XST_SUCCESS) {
    	printf("\n\r XScuGic_Connect() with timer failed\n");
    }

    //enable the interrupt controller
    XScuGic_Enable(&intCtrl, TimerIntrID);

	// Set the timer to 100Hz
    XTmrCtr_SetOptions(&timer, 0,   XTC_INT_MODE_OPTION | XTC_AUTO_RELOAD_OPTION);
    XTmrCtr_SetResetValue(&timer, 0, TMR_LOAD(0.1)); // 100 Hz
    XTmrCtr_Start(&timer, 0);
}

int main() {
	/*------------------------------------------
	 * Initialize all the required modules
	 -------------------------------------------*/
	init_platform();
	initDisplay();
	initInterrupt();

	/*--------------------------------------
	 * Loop that read the XADC value and updates it
	 * After updating it sends the data to the PL using the GPIO
	 -------------------------------------*/
	while (1)
	{
	}
	return 0;
}
