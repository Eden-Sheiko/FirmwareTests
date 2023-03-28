#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

int main()
{
    // Open the I2C bus device file
    int fd = open("/dev/i2c-1", O_RDWR);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // Set the I2C slave address
    int addr = 50; // replace with your desired slave address
    if (ioctl(fd, I2C_SLAVE, addr) < 0) {
        perror("ioctl");
        close(fd); // Make sure to close the file descriptor before exiting
        exit(1);
    }

    // Prepare the input data to send to the slave device
    char buffer[50];
    int len = snprintf(buffer, 50, "i am data buffer from pi4b \n");

    // Write the input data to the slave device
    int write_len = write(fd, buffer, len);
    if (write_len < 0) {
        perror("write");
        close(fd); // Make sure to close the file descriptor before exiting
        exit(1);
    } else if (write_len != len) {
        fprintf(stderr, "Error: only %d bytes written instead of %d\n", write_len, len);
        close(fd); // Make sure to close the file descriptor before exiting
        exit(1);
    }

    // Close the I2C bus device file
    close(fd);

    return 0;
}
