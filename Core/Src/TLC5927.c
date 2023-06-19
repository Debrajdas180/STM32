/*
 * TLC5927.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Debraj Das
 */
#include "TLC5927.h"
#include <stdint.h>
#include "stm32f0xx_hal.h"
#include "main.h"
#include "stm32f0xx_hal_tim.h"

#define SDA_Pin GPIO_PIN_1 // edit the pin number as your require
#define SDA_GPIO_Port GPIOB // edit the port number as your require
#define LE_pin GPIO_PIN_10 // edit the pin number as your require
#define LE_GPIO_port GPIOB // edit the port number as your require
#define OE_pin GPIO_PIN_15 // edit the pin number as your require
#define OE_GPIO_port GPIOB // edit the port number as your require

extern TIM_HandleTypeDef htim1;


uint32_t var [] = { 0xffffc7e0 ,  //0
		            0x000fc0e0 , //1
					0xe3f1ffe0 , //2
					0xe07fffe0 , //3
					0x1c0ffee0 , //4
					0xfc7e3fe0 , //5
					0xfffe3fe0 , //6
					0xe00fc4e0 , //7
					0xffffffe0 , //8
					0xfc7fffe0 , //9
                   }; // values for 7 segment display driving

void high_low(int size){

static volatile int i , j  = 0;
    HAL_GPIO_WritePin(LE_GPIO_port, LE_pin, 0);
if (var[j] & (uint32_t)1<<i)
	HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, 1);
else
	HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, 0);
i++;
if (i==32){
	i = 0;
	HAL_GPIO_WritePin(LE_GPIO_port, LE_pin, 1);
	HAL_GPIO_WritePin(OE_GPIO_port, OE_pin, 0);
	j++;
}
if (j == size){
	j = 0 ;
			}
}

void disp_setNumber(uint8_t value){

	static volatile int i = 0;
	static volatile uint8_t digit ;
	uint32_t valurToShift;
	if(value!=0){
		digit =(value)-'0';
		valurToShift=var[digit];
	}
	else{
		valurToShift=0;
	}
    HAL_GPIO_WritePin(LE_GPIO_port, LE_pin, 0);
	  if (valurToShift & (uint32_t)1<<i){
	  	HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, 1);
	  }
	  else
	  	HAL_GPIO_WritePin(SDA_GPIO_Port, SDA_Pin, 0);
	  i++;
	  if (i==33){
	  	i = 0;
	  	HAL_GPIO_WritePin(LE_GPIO_port, LE_pin, 1);
	  	HAL_GPIO_WritePin(OE_GPIO_port, OE_pin, 0);
	  	HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
	  	  	  	  }
		}

