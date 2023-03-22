#include <stdio.h>
#include <pigpio.h>

int main() {
    int i2c_handle;
    int i2c_address = 0x40;
    int i2c_register = 0x00;
    int i2c_value = 0x01;

    // Initialize the PiGPIO library
    if (gpioInitialise() < 0) {
        printf("Error: Failed to initialize PiGPIO\n");
        return 1;
    }

    // Open the I2C device
    i2c_handle = i2cOpen(1, i2c_address, 0);
    if (i2c_handle < 0) {
        printf("Error: Failed to open I2C device\n");
        gpioTerminate();
        return 1;
    }

    // Write data to the I2C device
    if (i2cWriteByteData(i2c_handle, i2c_register, i2c_value) < 0) {
        printf("Error: Failed to write to I2C device\n");
        i2cClose(i2c_handle);
        gpioTerminate();
        return 1;
    }

    // Read data from the I2C device
    i2c_value = i2cReadByteData(i2c_handle, i2c_register);
    if (i2c_value < 0) {
        printf("Error: Failed to read from I2C device\n");
        i2cClose(i2c_handle);
        gpioTerminate();
        return 1;
    }

    // Print the read value
    printf("Read value: 0x%02x\n", i2c_value);

    // Close the I2C device
    i2cClose(i2c_handle);

    // Clean up the PiGPIO library
    gpioTerminate();

    return 0;
}
