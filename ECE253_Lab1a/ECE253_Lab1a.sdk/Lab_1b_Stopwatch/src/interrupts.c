/*
 * interrupts.c
 *
 *  Created on: Oct 9, 2021
 *      Author: jabbo
 */
#include "interrupts.h"

XIntc sys_intc;
XTmrCtr sys_tmrctr;
Xuint32 data;

int resetButton(){
	XStatus Status;
		/*
		 * Initialize the interrupt controller driver so that
		 * it is ready to use, specify the device ID that is generated in
		 * xparameters.h
		 */
		Status = XST_SUCCESS;
		Status = XIntc_Initialize(&sys_intc, XPAR_MICROBLAZE_0_AXI_INTC_DEVICE_ID);

		if ( Status != XST_SUCCESS )
		{
			if( Status == XST_DEVICE_NOT_FOUND )
			{
				xil_printf("XST_DEVICE_NOT_FOUND...\r\n");
			}
			else
			{
				xil_printf("a different error from XST_DEVICE_NOT_FOUND...\r\n");
			}


			xil_printf("Interrupt controller driver failed to be initialized...\r\n");
			return XST_FAILURE;
		}
}
