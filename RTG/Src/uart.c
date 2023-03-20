#include "RTG.h"


volatile uint8_t tx_flag_callback_success = FALSE;
volatile uint8_t rx_flag_callback_success = FALSE;


void send_data_uart() {
    HAL_StatusTypeDef status = HAL_OK;
    char buffer[BUFFER_SIZE];
    int len = snprintf(buffer, BUFFER_SIZE, "i am data buffer\n");
    printf("%s\n\r",buffer);
    if (len >= BUFFER_SIZE) {
        printf("overflow!\n\r");
        return;
    }
    status = HAL_UART_Transmit_IT(UART_4, (uint8_t*)buffer, len);
    if (status != HAL_OK) {
        char message[BUFFER_SIZE];
        int message_len = snprintf(message, BUFFER_SIZE, "Failed HAL_UART_Transmit: %d\n\r", status);
        if (message_len < BUFFER_SIZE) {
            HAL_UART_Transmit_IT(UART_4, (uint8_t*)message, message_len);
        }
        // Handle message truncation
    }
    else {
        HAL_UART_Transmit_IT(UART_4, (uint8_t*)"Data sent successfully.\n\r", sizeof("Data sent successfully.\n\r")-1);
    }
    //HAL_Delay(500); // wait for 500 milliseconds before sending again
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) { //got info good

	if (UART_4 == huart) {
		rx_flag_callback_success = TRUE;
	}

}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) { // send data good
	if (UART_4 == huart) {
		tx_flag_callback_success = TRUE;
	}
}

