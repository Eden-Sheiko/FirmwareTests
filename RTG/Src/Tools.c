#include "RTG.h"

// printf
int __io_putchar(int ch) {
	HAL_UART_Transmit(UART_DEBUGER, (uint8_t*) &ch, ONE_VAL, 0xFFFF);
	return ch;
}

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(UART_DEBUGER, (uint8_t*) ptr, len, 0xFFFF);
	return len;
}

// scanf
int _read(int file, char *ptr, int len) {
	int ch = ZERO_VAL;
	HAL_UART_Receive(UART_DEBUGER, (uint8_t*) &ch, ONE_VAL, HAL_MAX_DELAY);
	HAL_UART_Transmit(UART_DEBUGER, (uint8_t*) &ch, ONE_VAL, HAL_MAX_DELAY);
	if (ch == THIRTEEN_VAL) {
		ch = TEN_VAL;
		HAL_UART_Transmit(UART_DEBUGER, (uint8_t*) &ch, ONE_VAL, HAL_MAX_DELAY);
	} else if (ch == BITS_IN_BYTE) {
		ch = 0x30;
		HAL_UART_Transmit(UART_DEBUGER, (uint8_t*) &ch, ONE_VAL, HAL_MAX_DELAY);
	}

	*ptr = ch;

	return TRUE;
}
