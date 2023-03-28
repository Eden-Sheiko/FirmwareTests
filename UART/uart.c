//
// Created by pi on 09/03/23.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

int main() {
    int uart_filestream = -1;

    // Open UART port
    uart_filestream = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    if (uart_filestream == -1) {
        printf("Error opening UART port.\n");
        return -1;
    }

    // Configure UART port
    struct termios options;
    tcgetattr(uart_filestream, &options);
    /*
     * Retrieves the current terminal interface configuration and stores it in the "options" structure.
     */
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    /*
     * Sets the terminal interface configuration options:
     * 	B115200- specifies the baud rate.
     * 	CS8 constant specifies 8 data bits.
     * 	CLOCAL and CREAD constants enable the receiver and set the port to operate in local mode, respectively.
     */
    options.c_iflag = IGNPAR;
    /*
     * sets the input mode flags.
     * The IGNPAR constant specifies that input bytes with a framing or parity error should be ignored.
     */
    options.c_oflag = 0;
    /*
     * Sets the output mode flags to 0, which disables all output processing.
     */
    options.c_lflag = 0;
    /*
     * Sets the local mode flags to 0, which disables all local processing.
     */
    tcflush(uart_filestream, TCIFLUSH);
    /*
     * This function flushes the input buffer of the terminal interface.
     */
    tcsetattr(uart_filestream, TCSANOW, &options);
    /*
     * This function sets the terminal interface configuration
     * to the values specified in the options structure.
     */

    // Read data from UART in a loop
    while (1) {
        char buf[50];
        int bytes_read = read(uart_filestream, buf, sizeof(buf) - 1);
        if (bytes_read < 0) {
            printf("Failed to read from UART: %s\n", strerror(errno));
        } else if (bytes_read > 0) {
            buf[bytes_read] = '\0'; // add null terminator
            //printf("Received %d bytes: %s\n", bytes_read, buf);
            fwrite(buf, 1, bytes_read, stdout);
        } else {
            // no data received, do something else
            usleep(1000000);
        }
    }


    // Close UART port
    close(uart_filestream);

    return 0;
}

