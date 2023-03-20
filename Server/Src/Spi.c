#include "../Inc/Spi.h"

uint8_t SPI_slave_callback_success = FALSE;
uint8_t SPI_master_callback_success = FALSE;

uint8_t SPI_send(uint8_t data_size, uint8_t *data_sent, uint8_t iteration) {
	uint8_t buffer_send[BUFFER_SIZE];
	uint8_t buffer_receive[BUFFER_SIZE];
	HAL_StatusTypeDef status_1 = HAL_OK;
	HAL_StatusTypeDef status_2 = HAL_OK;
	HAL_StatusTypeDef status_3 = HAL_OK;
	HAL_StatusTypeDef status_4 = HAL_OK;

	status_1 = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, buffer_send, buffer_send, data_size);
	status_2 = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, data_sent, buffer_receive,data_size);
	check_status(&status_1, &status_2);

	while (iteration) {
		if (SPI_slave_callback_success) {
			printf("Data_Sent: %s\r\n", buffer_send);

			status_3 = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, buffer_send, buffer_send,data_size);
			status_4 = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, buffer_receive,buffer_receive, data_size);
			check_status(&status_3, &status_4);

			SPI_slave_callback_success = FALSE;
		}
		if (SPI_master_callback_success) {
			printf("Data_Received: %s\r\n", buffer_receive);

			SPI_master_callback_success = FALSE;

		}
		iteration--;
		if (iteration) {
			compare_arrays(buffer_receive, data_sent, data_size);
			status_1 = HAL_SPI_TransmitReceive_DMA(SPI_SLAVE, buffer_send, buffer_send, data_size);
			status_2 = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, data_sent, buffer_receive,data_size);
			check_status(&status_1, &status_2);
		}
	}
	return TRUE;
}


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
	if (hspi == SPI_SLAVE)
		SPI_slave_callback_success = TRUE;
	if (hspi == SPI_MASTER)
		SPI_master_callback_success = TRUE;
}

