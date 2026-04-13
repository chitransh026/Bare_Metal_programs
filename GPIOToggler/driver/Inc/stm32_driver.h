/*
 * stm32_driver.h
 *
 *  Created on: May 16, 2025
 *      Author: lenovo
 */

#ifndef INC_STM32_DRIVER_H_
#define INC_STM32_DRIVER_H_

#include "stm32f401.h"
#include<stdint.h>

typedef struct{
    uint32_t GPIO_PinNumber;
	uint32_t GPIO_PinMode;
	uint32_t GPIO_PinSpeed;
	uint32_t GPIO_PinPuPdControl;
	uint32_t GPIO_PinOPtype;
	uint32_t GPIO_PinAltFun;
}GPIO_pinconfig_t;

typedef struct{
	GPIO_regdef_t *pGPIOx;
	GPIO_pinconfig_t GPIO_PinConfig;
}GPIO_Handle_t;

void GPIO_PeriClockControl(GPIO_regdef_t *pGPIOx, uint8_t EnorDi);
void GPIO_Inti(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_regdef_t *pGPIOx);

uint8_t GPIO_ReadFromInputPin(GPIO_regdef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_regdef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_regdef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WriteToOutputPort(GPIO_regdef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_regdef_t *pGPIOx, uint8_t PinNumber);

#define GPIO_MODE_IN        0
#define GPIO_MODE_OUT       1
#define GPIO_MODE_ALTFN     2
#define GPIO_MODE_ANALOG    3
#define GPIO_MODE_IT_FT     4
#define GPIO_MODE_IT_RT     5
#define GPIO_MODE_IT_RFT    6




#endif /* INC_STM32_DRIVER_H_ */
