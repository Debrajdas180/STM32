/*
 * TLC5927.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Debraj Das
 */

#ifndef INC_TLC5927_H_
#define INC_TLC5927_H_
#include <stdint.h>

void high_low(int size); // for printing 0 - 9 digit with its size
void disp_setNumber(uint8_t *value); // for printing UART data to display


#endif /* INC_TLC5927_H_ */
