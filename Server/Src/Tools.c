#include "../Inc/Server_Main.h"

/*
 *  4B       1B               			1b				1b		8b - 64 bit 4b 32bit
 *   +------+----------+---+--------+---~~--+---------+--------+---~~---+
 *   | TEST ID | Peripheral to be tested |  Iterations  |length |  *string |
 *   +------+----------+---+--------+---~~--+---------+--------+---~~---+
 */
/**
 * resv_t - is the packet  that being send to the
 * UDP server from the UDP client
 * @brief resv_t contains 5 types:
 * Test_id type:[uint32_t]
 * Peripheral type:[uint8_t]
 * Iterations type:[uint8_t]
 * length type:[uint8_t]
 * msg type:[char]
 */
typedef struct resv {
	uint32_t Test_id;
	uint8_t Peripheral;
	uint8_t Iterations;
	uint8_t length;
	char msg[BUFFER_MSG];
} resv_t;

/*
 *  4B       1B
 *   +------+----------+---+--~~---+
 *   | TEST ID | Test_result       |
 *   +------+----------+---+--~~---+
*/

/**
 * res_t is the result that being send to the client
 * @brief res_t contains 2 types
 * Test_id type:[uint32_t]
 * Test_result type:[uint8_t]
 */

typedef struct res{
	uint32_t Test_id;
	uint8_t Test_result;
}res_t;

void udp_receive_callback(void *arg, struct udp_pcb *upcb, struct pbuf *p,
		const ip_addr_t *addr, u16_t port) {
	struct pbuf *txBuf;
	// creating instance of res_t struct
	// creating instance of resv_t struct
	resv_t paket = {ZERO};
	res_t answer = {ZERO};
	uint8_t status = ZERO;
	/* Get the IP of the Client */
	const char *remoteIP = ipaddr_ntoa(addr);
	//crating new buffer
	char buf[BUFFER_NET_SIZE];
	//setting buffer to 0
	memset(buf, ZERO, BUFFER_NET_SIZE);


	int len = sprintf(buf, "%s hello from udp server\n", (char*) p->payload);


	// getting the data from the payload to buffer
	memcpy(buf, (p->payload), BUFFER_NET_SIZE);

	//updating len
	len = p->len;

	// transforming the buffer to struct
	memcpy(&paket, buf, BUFFER_NET_SIZE);

	if (paket.Peripheral == TIMER_ID) {
		status = TIMER_test();
	}
	else if (paket.Peripheral == UART_ID) {
		status = UART_send(paket.length,paket.msg,paket.Iterations);
	}
	else if (paket.Peripheral == SPI_ID) {
		status = SPI_send(paket.length,paket.msg,paket.Iterations);
	}
	else if (paket.Peripheral == I2C_ID) {
		status = I2C_send(paket.length,paket.msg,paket.Iterations);
	}
	else if (paket.Peripheral == ADC_ID) {
		status = ADC_test();
	}

	// updating the data
	answer.Test_id = paket.Test_id;
	answer.Test_result = status;

	//updating the new buffer
	memcpy(buf,&answer,sizeof(answer));

	/* allocate pbuf from RAM*/
	txBuf = pbuf_alloc(PBUF_TRANSPORT, len, PBUF_RAM);

	/* copy the data into the buffer  */
	pbuf_take(txBuf, buf, len);

	/* Connect to the remote client */
	udp_connect(upcb, addr, port);

	/* Send a Reply to the Client */
	udp_send(upcb, txBuf);

	/* free the UDP connection, so we can accept new clients */
	udp_disconnect(upcb);

	/* Free the p_tx buffer */
	pbuf_free(txBuf);

	/* Free the p buffer */
	pbuf_free(p);
}

void udpServer_init(void) {
	// UDP Control Block structure
	struct udp_pcb *upcb = udp_new();
	err_t err = udp_bind(upcb, IP_ADDR_ANY, SERVER_PORT); // 7 is the server UDP port

	/* 3. Set a receive callback for the upcb */
	if (err == ERR_OK) {
		udp_recv(upcb, udp_receive_callback, NULL);
	} else {
		udp_remove(upcb);
	}
}

// print
int __io_putchar(int ch) {
	HAL_UART_Transmit(UART_DEBUG, (uint8_t*) &ch, BYTE, HAL_MAX_DELAY);
	return ch;
}

int _write(int file, char *ptr, int len) {
	HAL_UART_Transmit(UART_DEBUG, (uint8_t*) ptr, len, HAL_MAX_DELAY);
	return len;
}

// scan
int __io_getchar(void) {
	uint8_t ch = ZERO;
	HAL_UART_Receive(UART_DEBUG, &ch, BYTE, HAL_MAX_DELAY);
	HAL_UART_Transmit(UART_DEBUG, &ch, BYTE, HAL_MAX_DELAY);
	return ch;
}

int _read(int file, char *ptr, int len) {
	int DataIdx = ZERO;
	char ch;
	int counter = ZERO;
	for (; DataIdx < len; DataIdx++) {
		ch = __io_getchar();
		*ptr = ch;
		ptr++;
		if (ch == CARRIAGE_RETURN || ch == LINE_FEED) {
			*(ptr) = ZERO;
			break;
		}
	}
	return DataIdx + BYTE;
}
