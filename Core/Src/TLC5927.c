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

#define SDA_Pin GPIO_PIN_1 // edit the pin number as your require
#define SDA_GPIO_Port GPIOB // edit the port number as your require
#define LE_pin GPIO_PIN_10 // edit the pin number as your require
#define LE_GPIO_port GPIOB // edit the port number as your require
#define OE_pin GPIO_PIN_15 // edit the pin number as your require
#define OE_GPIO_port GPIOB // edit the port number as your require



void high_low(uint32_t arr[],int size){

static volatile int i , j  = 0;
    HAL_GPIO_WritePin(LE_GPIO_port, LE_pin, 0);
if (arr[j] & (uint32_t)1<<i)
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
