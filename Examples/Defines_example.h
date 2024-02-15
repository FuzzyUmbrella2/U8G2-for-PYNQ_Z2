// The defines for the SH1106 screen
#define SlaveAddress 0x3c				// Adress to which the data is send
#define IIC_SCLK_RATE 400000			// the clock rate of the screen and IIC
#define UsedFont u8g2_font_t0_11_me		// The font used to print

#define GpioID XPAR_GPIO_AXI_GPIO_0_DEVICE_ID

#define XAdcID XPAR_XADCPS_0_DEVICE_ID

#define GicID XPAR_PS7_SCUGIC_0_DEVICE_ID

#define TimerID XPAR_TMRCTR_0_DEVICE_ID
#define TimerIntrID XPAR_FABRIC_INTERRUPTS_AXI_TIMER_0_INTERRUPT_INTR

// The defines for the timer
#define MAX_COUNT  0xFFFFFFFF					// The maximum value from which the timers can count down
#define PB_FRQ 100000000 //100MHz				// frequency of the timers
#define TMR_LOAD(per)  (u32)((int)MAX_COUNT + 2 - (int)(per * (float)PB_FRQ)) //calculates the right value using the periode in secondes
