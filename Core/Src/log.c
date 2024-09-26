/*
 * log.c
 *
 *  Created on: Sep 26, 2024
 *      Author: DEBRAJ DAS
 */


#include "log.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static UART_HandleTypeDef *huart_log;  // UART handler for logging

static UART_HandleTypeDef *huart_log;  // UART handler for logging

// ANSI escape codes for colors
#define ANSI_COLOR_RED    "\033[31m"
#define ANSI_COLOR_GREEN  "\033[32m"
#define ANSI_COLOR_YELLOW "\033[33m"
#define ANSI_COLOR_RESET  "\033[0m"

// Initialize UART for logging
void uart_log_init(UART_HandleTypeDef *huart) {
    huart_log = huart;
}

// Helper function to send a string over UART
static void uart_send_string(const char *str) {
    HAL_UART_Transmit(huart_log, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}

// Logging function with log level
void uart_log(LogLevel level, const char *fmt, ...) {
    char log_buffer[256];
    va_list args;

    // Choose color based on log level
    const char *color;
    switch (level) {
        case LOG_INFO:
        	 strcpy(log_buffer, "[INFO] ");
            color = ANSI_COLOR_GREEN;  // Info in green
            break;
        case LOG_WARNING:
        	strcpy(log_buffer, "[WARNING] ");
            color = ANSI_COLOR_YELLOW; // Warnings in yellow
            break;
        case LOG_ERROR:
        	strcpy(log_buffer, "[ERROR] ");
            color = ANSI_COLOR_RED;    // Errors in red
            break;
        default:
        	 strcpy(log_buffer, "[LOG] ");
            color = ANSI_COLOR_RESET;  // Default color
            break;
    }

    // Add the color code and log level prefix
    uart_send_string(color);

    // Format the user message
//
//      va_start(args, fmt);
//      vsnprintf(log_buffer, sizeof(log_buffer), fmt, args);
//      va_end(args);
      va_start(args, fmt);
       vsnprintf(log_buffer + strlen(log_buffer), sizeof(log_buffer) - strlen(log_buffer), fmt, args);
       va_end(args);



    // Send the formatted log message over UART
    uart_send_string(log_buffer);
    uart_send_string(ANSI_COLOR_RESET);  // Reset color after log
    uart_send_string("\r\n");
}

// Logging function without log level (raw log)
void uart_log_raw(const char *fmt, ...) {
    char log_buffer[256];
    va_list args;

    // Format the user message
    va_start(args, fmt);
    vsnprintf(log_buffer, sizeof(log_buffer), fmt, args);
    va_end(args);

    // Send the raw log message over UART
    uart_send_string(log_buffer);
    uart_send_string("\r\n");
}
