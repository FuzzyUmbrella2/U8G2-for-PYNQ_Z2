#include "SH1106Screen.h"

u8g2_t u8g2; // a structure which will contain all the data for one display
XIicPs Iic;
XIicPs_Config *Config;
int Status;
u8g2_uint_t DispHeight, DispWidth, CentreHeight, CentreWidth;
int8_t MaxStrHeight;

void initDisplay()
{
	// Setup function for the specific screen
	// Gets all the required data and links the CB function
    u8g2_Setup_sh1106_i2c_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_PYNQ_Z2_hw_i2c, u8x8_gpio_and_delay_sh1106);
    u8g2_InitDisplay(&u8g2);		// Send init sequence to the display, display is in sleep mode after this,
    u8g2_SetPowerSave(&u8g2, 0);	// Wake up display

    // Clear the buffer and the screen
    u8g2_ClearBuffer(&u8g2);
    u8g2_ClearDisplay(&u8g2);
    printf("Display is initialized\n");

    u8g2_SetFont(&u8g2, UsedFont);	// Update the font

    // Get variable data
    DispHeight = u8g2_GetDisplayHeight(&u8g2);
    CentreHeight = DispHeight/2;
    DispWidth = u8g2_GetDisplayWidth(&u8g2);
    CentreWidth = DispWidth/2;
    MaxStrHeight = u8g2_GetMaxCharHeight(&u8g2);
}

void printDisplay(u8g2_uint_t x, u8g2_uint_t y, const char *str)
{
	y = y+MaxStrHeight;		// starting point form bottom to top left
	u8g2_DrawStr(&u8g2, x, y, str);		// Send data to the buffer
	u8g2_SendBuffer(&u8g2);				// Send buffer to the screen
}

void printNewDisplay(u8g2_uint_t x, u8g2_uint_t y, const char *str)
{
	y = y+MaxStrHeight;		// starting point form bottom to top left
	u8g2_ClearBuffer(&u8g2);	// clear the buffer
    u8g2_ClearDisplay(&u8g2);	// clears the display
	u8g2_DrawStr(&u8g2, x, y, str);	// Send data to the buffer
	u8g2_SendBuffer(&u8g2);		// Send buffer to screen
}

void printCentreXDisplay(u8g2_uint_t y, const char *str)
{
	u8g2_uint_t x = CentreWidth-(u8g2_GetStrWidth(&u8g2, str)/2);	// Starting point on horizontal middle line
	y = y+MaxStrHeight;		// starting point form bottom to top left
	u8g2_DrawStr(&u8g2, x, y, str);	// Send data to buffer
	u8g2_SendBuffer(&u8g2);	// Send buffer to screen
}

void printNew_Centre_XY_Display(const char *str)
{
	u8g2_ClearBuffer(&u8g2);	// Clear the buffer
	u8g2_uint_t x = CentreWidth-(u8g2_GetStrWidth(&u8g2, str)/2);	// Starting point on horizontal middle line
	u8g2_uint_t y = CentreHeight+(MaxStrHeight/2);		// Starting point on right place for middle of the screen
	u8g2_DrawStr(&u8g2, x, y, str);		// Send data to the buffer
	u8g2_SendBuffer(&u8g2);	// Send the buffer to the display
}

void drawCentreXFrameWithTxt(u8g2_uint_t y, const char *str)
{
	u8g2_uint_t w = u8g2_GetStrWidth(&u8g2, str)+ 4;		// Get the needed width of the frame
	u8g2_uint_t h = ((u8g2_uint_t) MaxStrHeight)+ 3;		// Get the needed heigth of the frame
	u8g2_uint_t xBox = CentreWidth-(w/2);	// set x startin point of frame
	u8g2_uint_t xTxt = xBox + 2;			// Set x staring point of text
	u8g2_uint_t yTxt = y+h-3;				// Set y starting point of text
	u8g2_DrawFrame(&u8g2, xBox, y, w, h);	// Send frame data to buffer
	u8g2_DrawStr(&u8g2, xTxt, yTxt, str);	// Send text data to buffer
	u8g2_SendBuffer(&u8g2);	// Send buffer to the screen
}

uint8_t u8x8_gpio_and_delay_sh1106(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch(msg)
  {
      case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
        break;
      case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
        break;
      case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
        break;
      case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
        break;
      case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
      //case U8X8_MSG_GPIO_SPI_CLOCK:
        break;
      case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
      //case U8X8_MSG_GPIO_SPI_DATA:
        break;
      case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
        break;
      case U8X8_MSG_GPIO_MENU_SELECT:
        u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
        break;
      case U8X8_MSG_GPIO_MENU_NEXT:
        u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
        break;
      case U8X8_MSG_GPIO_MENU_PREV:
        u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
        break;
      case U8X8_MSG_GPIO_MENU_HOME:
        u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
        break;
    case U8X8_MSG_GPIO_AND_DELAY_INIT:
      break;
    case U8X8_MSG_DELAY_I2C:
      break;
    case U8X8_MSG_GPIO_I2C_CLOCK:
      break;
    case U8X8_MSG_GPIO_I2C_DATA:
      break;
    default:
    	u8x8_SetGPIOResult(u8x8, 1);			// default return value
      break;
  }
  return 1;
}

uint8_t u8x8_byte_PYNQ_Z2_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	  static uint8_t buffer[32];		/* u8g2/u8x8 will never send more than 32 bytes between START_TRANSFER and END_TRANSFER */
	  static uint8_t buf_idx;
	  uint8_t *data;

	  switch(msg)
	  {
	  	  // Only called once to set up the IIC hardware in the right way
	    case U8X8_MSG_BYTE_INIT:
	    	// Look up the config of the IIC
	    	Config = XIicPs_LookupConfig(XPAR_XIICPS_0_DEVICE_ID);
	    	if (NULL == Config)
	    	{
	    		printf("XIicPs_LookupConfig failure\r\n");
	    		return XST_FAILURE;
	    	}
	    	// Initialize the IIC using the config
	    	if (XIicPs_CfgInitialize(&Iic, Config, Config->BaseAddress) != XST_SUCCESS)
	    	{
	    	   printf("XIicPs_CfgInitialize failure\r\n");
	    	   return XST_FAILURE;
	    	}
	    	// Do a selftest on the IIC struct to ensure it is working
	    	if (XIicPs_SelfTest(&Iic) != XST_SUCCESS)
	    	{
	    		printf("IIC selftest FAILED \r\n");
	    		return XST_FAILURE;
	    	}
	    	// Set the clock speed of the IIC bus
	    	if (XIicPs_SetSClk(&Iic, IIC_SCLK_RATE) != XST_SUCCESS)
	    	{
	    		printf("IIC setClock FAILED \r\n");
	    		return XST_FAILURE;
	    	}
	    	printf("IIC Passed\n");
	      break;

	      // Collects all the data in a buffer
	    case U8X8_MSG_BYTE_SEND:
	      data = (uint8_t *)arg_ptr;
	      while( arg_int > 0 )
	      {
		buffer[buf_idx++] = *data;
		data++;
		arg_int--;
	      }
	      break;

	    case U8X8_MSG_BYTE_SET_DC:
	      /* ignored for i2c */
	      break;
	    case U8X8_MSG_BYTE_START_TRANSFER:
	      buf_idx = 0;
	      break;

	      // Sends the data over the IIC bus
	    case U8X8_MSG_BYTE_END_TRANSFER:
	    	// Send the data and check if it is received properly
	    	Status = XIicPs_MasterSendPolled(&Iic, buffer, buf_idx, SH1106Address);
	    	if (Status != XST_SUCCESS)
	    	{
	    		xil_printf("XIicPs_MasterSendPolled failure Status = %d\r\n",Status);
	    	}
	      break;
	    default:
	      return 0;
	  }
	  return 1;
}
