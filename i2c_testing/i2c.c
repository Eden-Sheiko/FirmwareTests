#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <string.h>

#define DEVICE_ADDRESS 20 // STM32F746ZG I2C device address in decimal
#define I2C_BUS "/dev/i2c-1" // Use "/dev/i2c-1" for Raspberry Pi 4B, "/dev/i2c-0" for older models

int main() {
    int i2c_fd;
    int result;
    const char *buffer = "i am buffer i2c";
    size_t buffer_len = strlen(buffer);

    // Open the I2C device
    i2c_fd = open(I2C_BUS, O_RDWR);

    if (i2c_fd < 0) {
        perror("Error opening I2C device");
        return 1;
    }

    // Set the I2C slave address
    if (ioctl(i2c_fd, I2C_SLAVE, DEVICE_ADDRESS) < 0) {
        perror("Error setting I2C slave address");
        close(i2c_fd);
        return 1;
    }

    // Send the buffer
    result = write(i2c_fd, buffer, buffer_len);

    if (result < 0) {
        perror("Error sending I2C buffer");
        close(i2c_fd);
        return 1;
    }

    printf("Sent buffer: %s\n", buffer);

    close(i2c_fd);

    return 0;
}
