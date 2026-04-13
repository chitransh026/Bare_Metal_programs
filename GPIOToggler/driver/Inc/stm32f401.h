/*
 * stm32_driver.h
 *
 *  Created on: May 16, 2025
 *      Author: lenovo
 */

#ifndef INC_STM32_DRIVER_H_
#define INC_STM32_DRIVER_H_
#include<stdint.h>

#define FlashAddr          0x08000000U
#define ROMAddr            0x1FFF0000U
#define SramAddr           0x20000000U

#define Peri_base_addr     0x40000000U
#define AHB1_base_addr     0x40020000U
#define AHB2_base_addr     0x50000000U
#define APB2_base_addr     0x40010000U
#define APB1_base_addr     0x40000000U

#define GPIOA_base_addr    (AHB1_base_addr+0x000)
#define GPIOB_base_addr    (AHB1_base_addr+0x400)
#define GPIOC_base_addr    (AHB1_base_addr+0x800)
#define GPIOD_base_addr    (AHB1_base_addr+0xC00)
#define GPIOE_base_addr    (AHB1_base_addr+0x1000)
#define GPIOH_base_addr    (AHB1_base_addr+0x1C00)
#define RCC_base_addr      (AHB1_base_addr+0x3800)

typedef struct {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
}GPIO_regdef_t;

#define GPIOA ((GPIO_regdef_t*)GPIOA_base_addr)
#define GPIOB ((GPIO_regdef_t*)GPIOB_base_addr)
#define GPIOC ((GPIO_regdef_t*)GPIOC_base_addr)
#define GPIOD ((GPIO_regdef_t*)GPIOD_base_addr)
#define GPIOE ((GPIO_regdef_t*)GPIOE_base_addr)
#define GPIOH ((GPIO_regdef_t*)GPIOH_base_addr)


typedef struct {
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	volatile uint32_t Reserved0;
	volatile uint32_t Reserved1;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t Reserved2;
	volatile uint32_t Reserved3;
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	volatile uint32_t Reserved4;
	volatile uint32_t Reserved5;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t Reserved6;
	volatile uint32_t Reserved7;

} RCC_regdef_t;
#define RCC ((RCC_regdef_t*)RCC_base_addr)

#define GPIOA_PCLK_EN() (RCC->AHB1ENR |=(1<<0))
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |=(1<<1))
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |=(1<<2))
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |=(1<<3))
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |=(1<<4))
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |=(1<<7))

#define ENABLE               1
#define DISABLE              0
#define SET                  ENABLE
#define RESET                DISABLE
#define GPIO_PIN_SET         SET
#define GPIO_PIN_RESET       RESET
#define GPIO_MODE_IN        0
#define GPIO_MODE_OUT       1
#define GPIO_MODE_ALTFN     2
#define GPIO_MODE_ANALOG    3
#define GPIO_MODE_IT_FT     4
#define GPIO_MODE_IT_RT     5
#define GPIO_MODE_IT_RFT    6

#endif /* INC_STM32_DRIVER_H_ */
