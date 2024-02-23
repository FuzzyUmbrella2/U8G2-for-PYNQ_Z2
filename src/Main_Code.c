#include <stdio.h>
#include "platform.h"
#include "xparameters.h"
#include "xstatus.h"
#include "sleep.h"

#include "Defines.h"
#include "SH1106_Screen.h"

int main() {
	/*------------------------------------------
	 * Initialize all the required modules
	 -------------------------------------------*/
	init_platform();
	initDisplay();

	/*--------------------------------------
	 * Loop that read the XADC value and updates it
	 * After updating it sends the data to the PL using the GPIO
	 -------------------------------------*/
	while (1)
	{
		for(int i =0; i<20; i++)
		{
			if (i == 0)
			{
				printNew(0,0,"");
			}
			char buffer[20];
			sprintf(buffer, "i = %i\n",i);
			printDisplay(1, 1, "something is printed");
			printCentreX(20, buffer);
			usleep(1000);
		}
	}
	return 0;
}
