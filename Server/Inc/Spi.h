#ifndef INC_SPI_H_
#define INC_SPI_H_

/*
 * SPI (Master):
 *	PA5	SPI1_SCK
 *	PA6	SPI1_MISO
 *	PB5	SPI1_MOSI
 *
 * SPI (Slave):
 *  PE2	SPI4_SCK
 *	PE5	SPI4_MISO
 *	PE6	SPI4_MOSI
 */

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// SPI HANDLES:
extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi4;

// GENERAL DEFINITIONS:
#define BUFFER_SIZE 256

// BOOLS:
#define TRUE 1
#define FALSE 0
#define BYTE 1

//SPI:
#define SPI_MASTER &hspi1
#define SPI_SLAVE &hspi4


// FUNCTIONS:
/**
 * SPI_send
 *	@brief SPI_send is an SPI function that receives 3 params
 *	the function uses SPI protocol with SPI [(Master): &hspi1]
 *	and [SPI (Slave):&hspi4]
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
uint8_t SPI_send(uint8_t data_size,uint8_t *data_sent,uint8_t iteration);


#endif /* INC_SPI_H_ */
