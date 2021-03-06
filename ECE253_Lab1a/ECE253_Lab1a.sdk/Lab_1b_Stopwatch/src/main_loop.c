/*
 * main_loop.c
 *
 *  Created on: Oct 9, 2021
 *      Author: jabbo
 */
#include "sevenSeg_new.h"
#include "interrupts.h"
#include "main_loop.h"
#include "platform.h"
#include "XGpio.h"
XGpio LED_Gpio;
XGpio BTN_Gpio;
XIntc sys_intc;
XTmrCtr sys_tmrctr;
XTmrCtr loop_tmr;
static int btn_value;

u8 * BaseAddr = (u8 *) XPAR_MIG7SERIES_0_BASEADDR;


void btn_interrupt_handler(void *InstancePtr)
{
	XGpio_InterruptDisable(InstancePtr, BTN_INTERRUPT);

	if ((XGpio_InterruptGetStatus(InstancePtr) & BTN_INTERRUPT) != BTN_INTERRUPT)
	{
		return;
	}
	sevenseg_draw_digit(7, 0);
	int counting_enabled = 0;
	xil_printf("made it to the interrupt handler!");
	//connect to button gpio
	btn_value = XGpio_DiscreteRead(InstancePtr, 1);

	if (btn_value == 0b010000)
	//reset
	{
		if (counting_enabled == 0)
		{
		//Put a zero in the load register
		XTmrCtr_SetLoadReg(XPAR_TMRCTR_0_BASEADDR, 1, 0);
		sevenseg_draw_digit(1, 0);
		XGpio_DiscreteWrite(&LED_Gpio, 1, 0x1);
		//Copy the load register into the counter register
		XTmrCtr_SetControlStatusReg(XPAR_TMRCTR_0_BASEADDR, 1, XTC_CSR_LOAD_MASK);
		 //END TIMER RESET CODE
		}
	}
	else if (btn_value == 0b0000001)
	//start counting up
	{
		XTmrCtr_SetControlStatusReg(XPAR_TMRCTR_0_BASEADDR, 1,	XTC_CSR_ENABLE_TMR_MASK);
		counting_enabled = 1;
	}
	else if (btn_value == 0b00000010)
	//stop counting
	{
		XTmrCtr_SetControlStatusReg(XPAR_TMRCTR_0_BASEADDR, 1, 0);
		counting_enabled = 0;
	}

	(void) XGpio_InterruptClear(&BTN_Gpio, BTN_INTERRUPT);
	XGpio_InterruptEnable(&BTN_Gpio, BTN_INTERRUPT);

}
//int Interrupt_System_Setup(XIntc *XIntcInstancePtr)
//{
//	XGpio_InterruptEnable(&BTN_Gpio, BTN_INTERRUPT);
//	XGpio_InterruptGlobalEnable(&BTN_Gpio);
//	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
//			(Xil_ExceptionHandler) XIntc_InterruptHandler,
//			XIntcInstancePtr);
//	Xil_ExceptionEnable();
//	return XST_SUCCESS;
//}

int Init_Button_Intc(u16 device, XGpio *GpioInstance)
{
	XStatus Status;
	Status = XIntc_Initialize(&sys_intc, device);
	if ( Status != XST_SUCCESS )
		{
			xil_printf("interrupt controller initialization failed...\r\n");
			return XST_FAILURE;
		}
	//Status = Interrupt_System_Setup(&sys_intc);
	if ( Status != XST_SUCCESS )
			{
				xil_printf("Xintc connection failed...\r\n");
				return XST_FAILURE;
			}
	Status = XIntc_Connect(&sys_intc, XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_BTN_IP2INTC_IRPT_INTR, (XInterruptHandler)btn_interrupt_handler, (void*)GpioInstance);
	if ( Status != XST_SUCCESS )
		{
			xil_printf("Xintc connection failed...\r\n");
			return XST_FAILURE;
		}
	Status = XIntc_Start(&sys_intc, XIN_REAL_MODE);
	if ( Status != XST_SUCCESS )
			{
				xil_printf("Start interrupt controller failed\r\n");
				return XST_FAILURE;
			}
	XGpio_InterruptEnable(GpioInstance, XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_BTN_IP2INTC_IRPT_INTR);
	XGpio_InterruptGlobalEnable(GpioInstance);

	XIntc_Enable(&sys_intc, XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_BTN_IP2INTC_IRPT_INTR);
	microblaze_register_handler((XInterruptHandler)XIntc_DeviceInterruptHandler,
				(void*)XPAR_INTC_0_DEVICE_ID);

	microblaze_enable_interrupts();
	return XST_SUCCESS;
}

int main(void){
	int status;
	init_platform();
	XGpio_Initialize(&LED_Gpio, LED_DEVICE_ID);
	XGpio_Initialize(&BTN_Gpio, BTN_DEVICE_ID);
	XGpio_SetDataDirection(&BTN_Gpio, 1, 0xFF);
	status = Init_Button_Intc(INTC_DEVICE_ID, &BTN_Gpio);
	if ( status != XST_SUCCESS )
				{
					xil_printf("Init_Button_Intc\r\n");
					return XST_FAILURE;
				}
	//XTmrCtr_Initialize(&sys_tmrctr, XPAR_MICROBLAZE_0_AXI_INTC_DEVICE_ID);
	//XTmrCtr_SetOptions(&sys_tmrctr, 0, XTC_AUTO_RELOAD_OPTION);
	//XTmrCtr_SetResetValue(&sys_tmrctr, 0, 0x0);
	//XTmrCtr_Initialize(&loop_tmr, XPAR_MICROBLAZE_0_AXI_INTC)
	//sevenseg_draw_digit(0,1);
	while(1) {
		//time = XTmrCtr_GetValue(&sys_tmrctr, 0);
		//sevenseg_draw_digit(0, (int)(time * 10000) % 10);
		//sevenseg_draw_digit(1, (int)(time * 1000) % 10);
		//sevenseg_draw_digit(2, (int)(time * 100) % 10);
		//sevenseg_draw_digit(3, (int)(time * 10) % 10);
		//sevenseg_draw_digit(4, (int)(time) % 10);
		//sevenseg_draw_digit(5, (int)(time) % 100 / 10);
		//sevenseg_draw_digit(6, (int)(time) % 1000 / 100);
		//sevenseg_draw_digit(7, (int)(time) % 10000 / 1000);
		sevenseg_draw_digit(0, 1);
		sevenseg_turn_off(0);
		//sevenseg_draw_digit(1, 2);
		sevenseg_draw_digit(2, 3);

	}

}

