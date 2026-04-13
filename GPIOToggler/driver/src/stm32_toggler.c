/*
 * stm32_toggler.c
 *
 *  Created on: May 16, 2025
 *      Author: lenovo
 */
#include "stm32f401.h"


#include <stdint.h>
#include <stdlib.h>
void GPIO_PeriClockControl(GPIO_regdef_t *pGPIOx, uint8_t EnorDi){
    if(EnorDi == ENABLE){
        if(pGPIOx == GPIOA) RCC->RCC_AHB1ENR |= (1 << 0);
        else if(pGPIOx == GPIOB) RCC->RCC_AHB1ENR |= (1 << 1);
        else if(pGPIOx == GPIOC) RCC->RCC_AHB1ENR|= (1 << 2);
        else if(pGPIOx == GPIOD) RCC->RCC_AHB1ENR |= (1 << 3);
        else if(pGPIOx == GPIOE) RCC->RCC_AHB1ENR |= (1 << 4);
        else if(pGPIOx == GPIOH) RCC->RCC_AHB1ENR |= (1 << 7);
    }
    else{
        if(pGPIOx == GPIOA) RCC->RCC_AHB1ENR&= ~(1 << 0);
        else if(pGPIOx == GPIOB) RCC->RCC_AHB1ENR &= ~(1 << 1);
        else if(pGPIOx == GPIOC) RCC->RCC_AHB1ENR &= ~(1 << 2);
        else if(pGPIOx == GPIOD) RCC->RCC_AHB1ENR &= ~(1 << 3);
        else if(pGPIOx == GPIOE) RCC->RCC_AHB1ENR &= ~(1 << 4);
        else if(pGPIOx == GPIOH) RCC->RCC_AHB1ENR &= ~(1 << 7);
    }
}




void GPIO_Inti(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp = 0;

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
	    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <<(2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	    pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // Clear bits
	    pGPIOHandle->pGPIOx->MODER |= temp; // Set bits
	}
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType <<
	        pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);

	pGPIOHandle->pGPIOx->OTYPER &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed <<
	        (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 <<
	        (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl <<
	        (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 <<
	        (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
	    uint8_t afr_index = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
	    uint8_t afr_pos = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;

	    pGPIOHandle->pGPIOx->AFR[afr_index] &= ~(0xF << (4 * afr_pos));
	    pGPIOHandle->pGPIOx->AFR[afr_index] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * afr_pos));
	}

}
void GPIO_DeInti(GPIO_regdef_t *pGPIOx)
{
	if(pGPIOx==GPIOA)
	{
		RCC->RCC_AHB1ENR |=(1<<0);
		RCC->RCC_AHB1ENR &=~(1<<0);
	}
	else if(pGPIOx==GPIOB){
		RCC->RCC_AHB1ENR |=(1<<1);
		RCC->RCC_AHB1ENR &=~(1<<1);
	}
	else if(pGPIOx==GPIOC){
			RCC->RCC_AHB1ENR |=(1<<2);
			RCC->RCC_AHB1ENR &=~(1<<2);
		}
	else if(pGPIOx==GPIOD){
			RCC->RCC_AHB1ENR |=(1<<3);
			RCC->RCC_AHB1ENR&=~(1<<3);
		}
	else if(pGPIOx==GPIOE){
			RCC->RCC_AHB1ENR |=(1<<4);
			RCC->RCC_AHB1ENR
			&=~(1<<4);

		}
	else if(pGPIOx==GPIOH){
			RCC->RCC_AHB1ENR|=(1<<7);
			RCC->RCC_AHB1ENR&=~(1<<7);

		}

}
uint8_t GPIO_ReadFromInputPin(GPIO_regdef_t *pGPIOx, uint8_t PinNumber)
{
    uint8_t value;

    // Step 1: Read IDR register and right-shift by PinNumber
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x1);

    return value;
}
uint16_t GPIO_ReadFromInputPort(GPIO_regdef_t *pGPIOx)
{
    uint16_t value;

    // Step 1: Read the IDR (Input Data Register) as-is
    value = (uint16_t)(pGPIOx->IDR);

    return value;
}






