/*
 * log.h
 *
 *  Created on: Sep 26, 2024
 *      Author: DEBRAJ DAS
 */

#ifndef INC_LOG_H_
#define INC_LOG_H_


#include "stm32f0xx_hal.h"  // Replace 'xxx' with your STM32 series

// Log levels (optional)
typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
} LogLevel;

// Initialization function for UART logging
void uart_log_init(UART_HandleTypeDef *huart);

// Logging functions
void uart_log(LogLevel level, const char *fmt, ...);
void uart_log_raw(const char *fmt, ...);


#endif /* INC_LOG_H_ */
