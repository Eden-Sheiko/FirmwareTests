#include "../Inc/Server_Main.h"

/*
 *	This example will show how to transmit and receive
 *	packets using the LWIP. The following code will
 *	program the EVB to be an echo server.
 *
 *	EVB configuration:
 *	IP: 		192.168.1.2
 *	NETMASK: 	255.255.255.0 (or 0.0.0.0/24)
 *	GATEWAY: 	192.168.1.100 (not in use but required by IDE)
 *	Port:		7 (recommended 50,000+)
 */

void server_main_program() {
	printf("Start of SERVER\n\r");
	//udpServer_init();					//UDP server initialization
	while (TRUE) {
		ethernetif_input(&gnetif);		//Handles the actual reception of bytes from the network interface
		sys_check_timeouts();			//Handle which checks timeout expiration

	}
}



