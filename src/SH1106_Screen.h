#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"

#include "I2Csrc/u8x8.h"
#include "I2Csrc/u8g2.h"
#include "xiicps.h"
#include "Defines.h"


/*--------------------------------------------------------------
 * Function for initializing and configuring the display
 * Saves the screen data and links the different CB functions
 * No returns
 ---------------------------------------------------------------*/
void initDisplay();


/*------------------------------------------------------------
 * Functions for printing on the display
 * Can print on any desired space
 * while keeping the old data on the screen
 * Starts writing from the top left corner
 *
 * Inputs:
 * 		x	=	the x-axis offset
 * 		y	=	the y-axis offset
 * 		str	=	a string or char[] that needs to be printed
 *
 * No returns;
 -----------------------------------------------------------*/
void printDisplay(u8g2_uint_t x, u8g2_uint_t y, const char *str);


/*-----------------------------------------------------------
 * Function for printing on the display
 * Erases old data off the screen
 * Can print on any desired space
 * Starts writing from the top left corner
 *
 * Inputs:
 * 		x	=	the x-axis offset
 * 		y	=	the y-axis offset
 * 		str	=	a string or char[] that needs to be printed
 *
 * No returns;
 ----------------------------------------------------------*/
void printNewDisplay(u8g2_uint_t x, u8g2_uint_t y, const char *str);


/*-----------------------------------------------------------
 * Function for printing on the display
 * Keeps old data on the screen
 * Always prints on the horizontal mid line
 * Starts writing from the top left corner
 *
 * Input:
 * 		y	=	the y-axis offset
 * 		str	=	a string or char[] that needs to be printed
 *
 * No returns;
----------------------------------------------------------- */
void printCentreXDisplay(u8g2_uint_t y, const char *str);


/*-----------------------------------------------------------
 * Function for printing in the middle of the display
 * Erases old data off the screen
 * Prints in the exact middle of the screen
 * starts writing from the top left corner
 *
 * Inputs:
 * 		str	=	a string or char[] that needs to be printed
 *
 * No returns;
 -----------------------------------------------------------*/
void printNew_Centre_XY_Display(const char *str);


/*-------------------------------------------------------------
 * Function for printing the text in a frame on the display
 * Keeps old data on the screen
 * Draws on the horizontal mid line
 * Starts on the top left corner
 *
 * Input:
 * 		y	=	the y-axis offset
 * 		str	=	a string or char[] that needs to be printed
 *
 * No returns;
 ------------------------------------------------------------*/
void drawCentreXFrameWithTxt(u8g2_uint_t y, const char *str);


/*-----------------------------------------------------------
 * Callback function that the U8G2 library uses
 * Takes care of the delays and initializing the gpio
 * Because HW IIC is used this function has no real meaning
 -----------------------------------------------------------*/
uint8_t u8x8_gpio_and_delay_sh1106(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);


/*--------------------------------------------------------------
 * Callback function that the U8G2 library uses
 * This function is the communication between the U8G2 library
 * and the HW IIC library of the PYNQ-Z2
 * It initializes the IIC, formats the data so it is transferable
 * and gives the command to the IIC library to send the data
 */
uint8_t u8x8_byte_PYNQ_Z2_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);