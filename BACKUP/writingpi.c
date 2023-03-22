#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringSerial.h>

int main()
{
    int uart_fd;
    char buffer[10];

    // Open the serial port
    if ((uart_fd = serialOpen("/dev/serial0", 9600)) < 0)
    {
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        return 1;
    }

    // Read a small buffer of data from the serial port
    serialRead(uart_fd, buffer, sizeof(buffer));

    // Print the received data
    printf("Received data: %s\n", buffer);

    // Close the serial port
    serialClose(uart_fd);

    return 0;
}
