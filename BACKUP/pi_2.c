#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int main()
{
    int fd = open("/dev/serial0", O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        perror("open failed");
        return 1;
    }

    struct termios options;
    tcgetattr(fd, &options);
    cfsetospeed(&options, B115200);
    cfsetispeed(&options, B115200);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 10; // set VTIME to 10, meaning 1 second timeout
    tcsetattr(fd, TCSANOW, &options);

    while (1)
    {
        char buf[100];
        int bytes_read = read(fd, buf, sizeof(buf) - 1);
        if (bytes_read < 0)
        {
            perror("read failed");
        }
        else if (bytes_read > 0)
        {
            buf[bytes_read] = '\0'; // add null terminator
            printf("Received %d bytes: %s\n", bytes_read, buf);
        }
        else
        {
            // no data received, do something else
            printf("No data received. Sleeping for 1 second...\n");
            sleep(1); // sleep for 1 second
        }
    }

    close(fd);
    return 0;
}
