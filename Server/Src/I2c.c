#include "../Inc/I2c.h"


volatile uint8_t i2c1_master_callback_success = FALSE;
volatile uint8_t i2c2_slave_callback_success = FALSE;

uint8_t I2C_send(uint8_t data_size, uint8_t *data_sent, uint8_t iteration) {
	uint8_t buffer_receive[BUFFER_SIZE];
	HAL_StatusTypeDef status_1 = HAL_OK;
	HAL_StatusTypeDef status_2 = HAL_OK;
	HAL_StatusTypeDef status_3 = HAL_OK;
	HAL_StatusTypeDef status_4 = HAL_OK;
	status_1 = HAL_I2C_Slave_Receive_DMA(I2C_SLAVE, buffer_receive, data_size);
	check_status(&status_1, &status_2);
	while (iteration) {
		if (i2c2_slave_callback_success) {

			printf("Data_receive: %s\r\n", buffer_receive);
			status_3 = HAL_I2C_Master_Receive_DMA(I2C_SLAVE, SLAVE_ADDRESS,buffer_receive, data_size);
			//status_4 = HAL_I2C_Slave_Transmit_DMA(I2C_SLAVE, buffer_send,data_size);
			check_status(&status_3, &status_4);
			i2c2_slave_callback_success = FALSE;

		}
		if (i2c1_master_callback_success) {
			printf("Data_Received: %s\r\n", buffer_receive);
			i2c1_master_callback_success = FALSE;
			iteration--;
			if (iteration) {
				//compare_arrays(buffer_send, data_sent, data_size);
				//status_1 = HAL_I2C_Slave_Receive_DMA(I2C_SLAVE, buffer_send,data_size);
				status_2 = HAL_I2C_Master_Transmit_DMA(I2C_SLAVE,SLAVE_ADDRESS, data_sent, data_size);
				check_status(&status_1, &status_2);
			}

		}

	}
	return TRUE;

}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c == I2C_SLAVE)
		i2c2_slave_callback_success = TRUE;

}

//void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
//	if (hi2c == I2C_MASTER)
//		i2c1_master_callback_success = TRUE;
//}

