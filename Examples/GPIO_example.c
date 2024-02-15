#include <stdio.h>

#include "Defines_example.h"
#include "platform.h"
#include "xparameters.h"
#include "xstatus.h"
#include "sleep.h"

#include "SH1106_Screen.h"

XGpio GPIO;

void initGPIO()
{
	int Status = XGpio_Initialize(&GPIO, GpioID);
	if (Status != XST_SUCCESS)
	{
		printf("GPIO initialize failed\n");
	}
	XGpio_SetDataDirection(&GPIO, 1, 0xF);			//Set data direction of channel 1 to all outputs
	printf("GPIO initialize succes\n");
}

int main() {
	/*------------------------------------------
	 * Initialize all the required modules
	 -------------------------------------------*/
	init_platform();
	initDisplay();
	initGPIO();

	/*--------------------------------------
	 * Loop that read the XADC value and updates it
	 * After updating it sends the data to the PL using the GPIO
	 -------------------------------------*/
	while (1)
	{
		int GpioMask = XGpio_DiscreteRead(&GPIO, 1);

		switch (GpioMask)
		{
		case 0b000:
			printNewMiddle("No button is pressed");
		case 0b0001:
			printNewMiddle("Button one is pressed");
			break;
		case 0b0010:
			printNewMiddle("Button two is pressed");
			break;
		case 0b0100:
			printNewMiddle("Button three is pressed");
			break;
		case 0b1000:
			printNewMiddle("Button four is pressed");
			break;
		default:
			printNewMiddle("To much buttons pressed");
			break;
		}

		usleep(500);
	}
	return 0;
}
