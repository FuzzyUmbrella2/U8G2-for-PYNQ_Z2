#include <stdio.h>

#include "Defines_example.h"
#include "platform.h"
#include "xparameters.h"
#include "xstatus.h"
#include "sleep.h"

#include "SH1106_Screen.h"

	XAdcPs XAdcInst;    		/* XADC driver instance */
	XAdcPs_Config *ConfigPtr;			// Pointer to the XADC config
	XAdcPs *XAdcInstPtr = &XAdcInst;	// pointer to the XADC instance

void initXADC()
{
	ConfigPtr = XAdcPs_LookupConfig(XAdcID);	// Configure the XADC
	if (ConfigPtr == NULL)		// Check if pointer is useable
	{
		printf("XADC lookup failed\n");
		return;
	}
	XAdcPs_CfgInitialize(XAdcInstPtr, ConfigPtr, ConfigPtr->BaseAddress); // initialize the configuration

	// self test the XADC instance
	int Status = XAdcPs_SelfTest(XAdcInstPtr);
	if (Status != XST_SUCCESS)
	{
		printf("XADC selftest failed\n");
		return;
	}

	XAdcPs_SetSequencerMode(XAdcInstPtr, XADCPS_SEQ_MODE_SAFE);
	XAdcPs_SetSequencerMode(XAdcInstPtr, XADCPS_SEQ_MODE_CONTINPASS);

	// self test the XADC instance
	int Status = XAdcPs_SelfTest(InstPtr);
	if (Status != XST_SUCCESS)
	{
		printf("Failed to configure XADC\n");
		return;
	}
	printf("Successfully configured XADC\n");
}

int main()
{
	/*------------------------------------------
	 * Initialize all the required modules
	 -------------------------------------------*/
	init_platform();
	initDisplay();
	initXADC();


	/*--------------------------------------
	 * Loop that read the XADC value and updates it
	 * After updating it sends the data to the PL using the GPIO
	 -------------------------------------*/
	while (1)
	{
		float ch0, ch1;	// variables that will store the XADC data
		char Str[32];	// BUffer that will be used to print the floats

		XAdcPs_Reset(&XAdcInst); //erase the old used values

		/*-----------------------------------------
		 * get the values of the XADC
		 * and turns it into the correct scale
		 * 0-3V3
		 ----------------------------------------*/
		ch0 = (s16)XAdcPs_GetAdcData(&XAdcInst,XADCPS_CH_AUX_MIN1);	// Get XADC value
		ch0 = (((float)(ch0)) * 3.3)/65536.0; // Calculate the corresponding voltage level

		ch1 = (s16)XAdcPs_GetAdcData(&XAdcInst,XADCPS_CH_AUX_MIN9);
		ch1 = (((float)(ch1)) * 3.3)/65536.0;

		sprintf(Str, "CH0 = .2%f", ch0);
		printCentreX(10, Str);
		sprintf(Str, ".2%f", ch1);
		printCentreX(20, "Value of CH1:");
		txtWthFrameCentreX(35, Str);
	}
	return 0;
}
