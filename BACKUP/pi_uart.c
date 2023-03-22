#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

int main() {
    int uart_filestream = open("dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (uart_filestream < 0) {
        printf("Failed to open UART: %s\n", strerror(errno));
        return 1;
    }

    struct termios options;
    tcgetattr(uart_filestream, &options);
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart_filestream, TCIFLUSH);
    tcsetattr(uart_filestream, TCSANOW, &options);

    while (1) {
        unsigned char buf[256];
        int bytes_read = read(uart_filestream, buf, sizeof(buf));
        if (bytes_read < 0) {
            printf("Failed to read from UART: %s\n", strerror(errno));
        } else if (bytes_read > 0) {
            printf("Received %d bytes:\n", bytes_read);
            for (int i = 0; i < bytes_read; i++) {
                printf("%02x ", buf[i]);
            }
            printf("\n");
        }
    }

    close(uart_filestream);
    return 0;
}
