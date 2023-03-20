#ifndef INC_UART_H_
#define INC_UART_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

// UART HANDLES:
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart6;

// UARAT AND GPIO DEFINITIONS:
#define UART_DEBUG &huart3			//Debug UART
#define UART_MASTER &huart4			//Transmit UART
#define UART_SLAVE &huart6			//Receive UART

// GENERAL DEFINITIONS:
#define BUFFER_SIZE 256

// BOOLS:
#define TRUE 1
#define BYTE 1
#define FALSE 0
#define ZERO 0
#define ERROR 0xff

// FUNCTIONS:
/**
 *  UART_send()
 *	@brief UART_send is an UART function that receives 3 params
 *	the function uses UART protocol with [UART_MASTER &huart4]
 *	and  [UART_SLAVE &huart6]
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
uint8_t UART_send(uint8_t data_size, uint8_t *data_sent, uint8_t iteration);

/**
 * check_status()
 * @brief is a function that receives two HAL_Status pointers and checks if
 * they are matching
 * @param *s1 - pointer to the first HAL_Status
 * @param *s2 - pointer to the second HAL_Status
 * if the function successful then it returns 1
 * else ( if it fails in the tests) returns 0xff
 *
 */
int check_status(HAL_StatusTypeDef *s1,HAL_StatusTypeDef *s2);

/**
 * compare_arrays()
 * @brief is a function that receives 2 uint8_t pointers and size
 * the function checks if the 2 buffers matching
 * @param *arr_1 - pointer to the first buffer.
 * @param *arr_2 - pointer to the second buffer.
 * @param size - size of the buffer.
 * if the function successful then it returns 1
 * else ( if it fails in the tests) returns 0xff
 *
 */
int compare_arrays(const uint8_t *arr_1 , const uint8_t *arr_2 ,const uint8_t size);


#endif /* INC_UART_H_ */
