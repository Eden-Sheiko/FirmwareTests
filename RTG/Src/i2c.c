#include "RTG.h"

// Global flag to indicate successful I2C slave receive callback
volatile uint8_t i2c_slave_callback_success = FALSE;

/**
 * @brief Receive data over I2C and print the received buffer.
 *
 * This function receives data from an I2C master, stores it in a buffer,
 * and prints the received buffer.
 */
void receive_data_i2c() {
    uint8_t buffer_receive[BUFFER_SIZE];

    // Receive data from I2C master synchronously
    HAL_StatusTypeDef status = HAL_I2C_Slave_Receive(I2C_SLAVE, buffer_receive, BUFFER_SIZE, HAL_MAX_DELAY);

    // Check for successful reception
    if (status == HAL_OK) {
        // Print received buffer
        printf("%s\n\r", buffer_receive);
    } else {
        // Print error message if data reception failed
        printf("Error receiving data over I2C: %d\n\r", status);
    }
}
