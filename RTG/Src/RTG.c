/****************************************************************************
 * RTG.c
 *
 * Author: Eden sheiko
 *
 * Testing PR
****************************************************************************/
#include "RTG.h"

void rtg_main() {
	while (TRUE) {
		//send_data_uart();
		//receive_data_i2c();
		send_spi_data();
	}
}


