#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_DEVICE "/dev/spidev0.0" // SPI device path
#define SPI_MODE   SPI_MODE_0       // SPI mode (CPOL=0, CPHA=0)
#define SPI_SPEED  1000000          // SPI clock speed
#define SPI_BITS   8                // SPI data length (8 bits)

int main()
{
    uint8_t buffer[32]; // Receive buffer

    // Open the SPI device
    int spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Set the SPI mode
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, SPI_MODE) < 0) {
        perror("ioctl SPI_IOC_WR_MODE");
        return EXIT_FAILURE;
    }

    // Set the SPI clock speed
    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, SPI_SPEED) < 0) {
        perror("ioctl SPI_IOC_WR_MAX_SPEED_HZ");
        return EXIT_FAILURE;
    }

    // Set the SPI data length
    if (ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, SPI_BITS) < 0) {
        perror("ioctl SPI_IOC_WR_BITS_PER_WORD");
        return EXIT_FAILURE;
    }

    // Receive data from the STM32 device
    struct spi_ioc_transfer tr = {
        .tx_buf = 0,
        .rx_buf = (unsigned long) buffer,
        .len = sizeof(buffer),
        .speed_hz = SPI_SPEED,
        .bits_per_word = SPI_BITS,
        .delay_usecs = 0,
    };
    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &tr) < 0) {
        perror("ioctl SPI_IOC_MESSAGE");
        return EXIT_FAILURE;
    }

    // Print the received data
    printf("Received data:");
    for (int i = 0; i < sizeof(buffer); i++) {
        printf(" 0x%02X", buffer[i]);
    }
    printf("\n");

    // Close the SPI device
    close(spi_fd);

    return EXIT_SUCCESS;
}
