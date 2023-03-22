#include "RTG.h"

// Global flag to indicate successful I2C slave receive callback
volatile uint8_t i2c2_slave_callback_success = FALSE;

/**
 * @brief Receive data over I2C and print the received buffer.
 *
 * This function receives data from an I2C master, stores it in a buffer,
 * and prints the received buffer.
 */
void receive_data_i2c() {
    uint8_t buffer_receive[BUFFER_SIZE];

    // Receive data from I2C master asynchronously
    HAL_StatusTypeDef status = HAL_I2C_Slave_Receive_IT(I2C_SLAVE, buffer_receive, BUFFER_SIZE);

    // Print received buffer
    printf("%s\n\r", buffer_receive);
}

/**
 * @brief Callback function for I2C slave receive completion.
 *
 * This function is called when the I2C slave has finished receiving data.
 * It sets the i2c2_slave_callback_success flag to TRUE if the receive
 * operation was successful.
 *
 * @param hi2c I2C handle for the callback
 */
void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    if (hi2c == I2C_SLAVE) {
        i2c2_slave_callback_success = TRUE;
    }
}
