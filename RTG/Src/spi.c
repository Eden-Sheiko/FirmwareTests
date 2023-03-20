#include "RTG.h"

volatile uint8_t SPI_master_callback_success = FALSE;


void send_spi_data(){
	HAL_StatusTypeDef status = HAL_OK;
	HAL_StatusTypeDef status2 = HAL_OK;
	char buffer[BUFFER_SIZE];
	int len = snprintf(buffer, BUFFER_SIZE, "i am data spi\n");
	printf("%s\n\r", buffer);
	//status = HAL_SPI_Transmit_IT(SPI_MASTER, (uint8_t*)buffer, len);
	status = HAL_SPI_Transmit_IT(SPI_MASTER, (uint8_t*)buffer, len);
	//status = HAL_SPI_TransmitReceive_IT(SPI_MASTER, (uint8_t*)buffer, (uint8_t*)buffer, len);
	//status = HAL_SPI_TransmitReceive_DMA(SPI_MASTER, (uint8_t*)buffer, (uint8_t*)buffer, len);


	//status2 = HAL_SPI_Transmit_IT(SPI_MASTER, (uint8_t*)buffer, len);
}


//void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
//	if (hspi == SPI_MASTER)
//		SPI_master_callback_success = TRUE;
//}

void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
	if (hspi == SPI_MASTER)
		SPI_master_callback_success = TRUE;
}

void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi) {
	if (hspi == SPI_MASTER)
		SPI_master_callback_success = TRUE;
}
