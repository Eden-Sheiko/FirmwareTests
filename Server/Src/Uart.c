#include "../Inc/Uart.h"

volatile uint8_t uart_slave_callback_success = FALSE;
volatile uint8_t uart_master_callback_success = FALSE;

uint8_t UART_send(uint8_t data_size, uint8_t *data_sent, uint8_t iteration) {
	uint8_t buffer_send[BUFFER_SIZE];
	HAL_StatusTypeDef status_1 = HAL_OK;
	HAL_StatusTypeDef status_2 = HAL_OK;
	HAL_StatusTypeDef status_3 = HAL_OK;
	HAL_StatusTypeDef status_4 = HAL_OK;

	//status_1 = HAL_UART_Receive_DMA(UART_SLAVE, buffer_send, data_size);
	status_2 = HAL_UART_Transmit_DMA(UART_MASTER, data_sent, data_size);
	//check_status(&status_1,&status_2);
	while (iteration) {
		printf("Data_Sent: %s\r\n", buffer_send);
		//status_3 = HAL_UART_Receive_DMA(UART_MASTER, buffer_receive,data_size);
		//status_4 = HAL_UART_Transmit_DMA(UART_SLAVE, buffer_send,data_size);
		//check_status(&status_4,&status_3);
		uart_slave_callback_success = FALSE;
	}
		if (uart_master_callback_success) {
			//printf("Data_Received: %s\r\n", buffer_receive);
			uart_master_callback_success = FALSE;
		}
			iteration--;
			if (iteration) {
				compare_arrays(buffer_send,data_sent,data_size);
				//status_1 = HAL_UART_Receive_DMA(UART_SLAVE, buffer_send,data_size);
				status_2 = HAL_UART_Transmit_DMA(UART_MASTER, data_sent,data_size);
				check_status(&status_1,&status_2);
				}
			return TRUE;
			}


int compare_arrays(const uint8_t *arr_1 , const uint8_t *arr_2 ,const uint8_t size){
	for (uint8_t i = ZERO; i < size; ++i) {
		if (arr_1[i] != arr_2[i]) {
			printf("arrays don't match-TEST FAILED\r\n");
			return ERROR;
		}
		printf("arrays match TEST PASSED\r\n");
		return TRUE;
	}
}

int check_status(HAL_StatusTypeDef *s1, HAL_StatusTypeDef *s2) {
	if (*s1 != HAL_OK || *s2 != HAL_OK) {
		printf("UART GPIO is disconnected\r\n");
		return ERROR;
	}
	return TRUE;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart == UART_MASTER)
		uart_master_callback_success = TRUE;
}

