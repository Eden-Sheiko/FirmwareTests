#ifndef INC_I2C_H_
#define INC_I2C_H_

/*
 * I2C1 (Master):
 * PB6	I2C1_SCL
 * PB9	I2C1_SDA
 *
 * I2C2 (Slave):
 * PB10	I2C2_SCL
 * PB11	I2C2_SDA

 *  Slave address: 20
 */

// includes
#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

// I2C HANDLES:
extern I2C_HandleTypeDef hi2c1;

// GENERAL DEFINITIONS:
#define BUFFER_SIZE 256
#define I2C_SLAVE &hi2c1
#define SLAVE_ADDRESS 20

// BOOLS:
#define TRUE 1
#define BYTE 1
#define FALSE 0
#define ZERO 0

// FUNCTIONS:
/**
 * I2C_send
 *	@brief I2C_send is an I2C function that receives 3 params
 *	the function uses I2C protocol with [I2C1 (Master)]
 *	and [I2C2 (Slave)].
 *	the function has basic error handling with using the HAL_OK API
 *	in addition there is a function that called compare_arrays which
 *	receives 2 buffers and compares them for more info see
 *	@see compare_arrays()
 * @param data_size - the size of the buffer that was send to the function.
 * @param *data_sent - pointer to the buffer.
 * @param iteration - number of iterations that the function will do.
 * if the function successful then it returns 1
 * else ( if it fails in the tests) returns 0xff
 */
uint8_t I2C_send(uint8_t data_size, uint8_t *data_sent, uint8_t iteration);

#endif /* INC_I2C_H_ */
