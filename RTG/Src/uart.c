#include "RTG.h"

// Global flags to indicate successful UART receive and transmit callbacks
volatile uint8_t tx_flag_callback_success = FALSE;
volatile uint8_t rx_flag_callback_success = FALSE;

/**
 * @brief Send data over UART and print the status of the transmission.
 *
 * This function sends data using UART and prints the status of the
 * transmission, whether it was successful or failed.
 */
void send_data_uart() {
    HAL_StatusTypeDef status;
    char buffer[BUFFER_SIZE];
    int len = snprintf(buffer, BUFFER_SIZE, "i am data buffer uart\n");

    printf("%s\n\r", buffer);

    if (len >= BUFFER_SIZE) {
        printf("overflow!\n\r");
        return;
    }

    status = HAL_UART_Transmit_IT(UART_4, (uint8_t *)buffer, len);

    if (status != HAL_OK) {
        char message[BUFFER_SIZE];
        int message_len = snprintf(message, BUFFER_SIZE, "Failed HAL_UART_Transmit: %d\n\r", status);

        if (message_len < BUFFER_SIZE) {
            HAL_UART_Transmit_IT(UART_4, (uint8_t *)message, message_len);
        }
        // Handle message truncation
    } else {
        HAL_UART_Transmit_IT(UART_4, (uint8_t *)"Data sent successfully.\n\r", sizeof("Data sent successfully.\n\r") - 1);
    }

    // HAL_Delay(500); // Wait for 500 milliseconds before sending again
}

/**
 * @brief Callback function for UART receive completion.
 *
 * This function is called when the UART has finished receiving data.
 * It sets the rx_flag_callback_success flag to TRUE if the receive
 * operation was successful.
 *
 * @param huart UART handle for the callback
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (UART_4 == huart) {
        rx_flag_callback_success = TRUE;
    }
}

/**
 * @brief Callback function for UART transmit completion.
 *
 * This function is called when the UART has finished transmitting data.
 * It sets the tx_flag_callback_success flag to TRUE if the transmit
 * operation was successful.
 *
 * @param huart UART handle for the callback
 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    if (UART_4 == huart) {
        tx_flag_callback_success = TRUE;
    }
}
