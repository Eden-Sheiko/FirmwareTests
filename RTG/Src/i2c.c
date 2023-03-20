#include "RTG.h"

volatile uint8_t i2c2_slave_callback_success = FALSE;


void receive_data_i2c(){
	uint8_t buffer_receive[BUFFER_SIZE];
	HAL_StatusTypeDef status_1 = HAL_OK;
	HAL_StatusTypeDef status_2 = HAL_OK;
	status_1 = HAL_I2C_Slave_Receive_IT(I2C_SLAVE, buffer_receive, BUFFER_SIZE);
	status_2 = HAL_I2C_Slave_Receive_IT(I2C_SLAVE, buffer_receive, BUFFER_SIZE);
    printf("%s\n\r",buffer_receive);
    //HAL_Delay(100);
}

void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c == I2C_SLAVE)
		i2c2_slave_callback_success = TRUE;

}
