/*
 * main_loop.h
 *
 *  Created on: Oct 9, 2021
 *      Author: jabbo
 */
#include "xtmrctr.h"
#include "xintc.h"
#include "xparameters.h"
#include "xtmrctr_l.h"
#include "xintc_l.h"
#include "mb_interface.h"
#include <xbasic_types.h>
#include <xio.h>
#ifndef SRC_MAIN_LOOP_H_
#define SRC_MAIN_LOOP_H_

#define INTC_DEVICE_ID	XPAR_INTC_0_DEVICE_ID
#define BTN_DEVICE_ID	XPAR_AXI_GPIO_BTN_DEVICE_ID
#define LED_DEVICE_ID	XPAR_AXI_GPIO_LED_DEVICE_ID
#define BTN_INTERRUPT	XPAR_AXI_GPIO_BTN_IP2INTC_IRPT_MASK

#endif /* SRC_MAIN_LOOP_H_ */
