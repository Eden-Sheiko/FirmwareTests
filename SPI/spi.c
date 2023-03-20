#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <string.h>

#define SPI_DEVICE "/dev/spidev0.0"
#define BUFFER_SIZE 32

int main(int argc, char **argv) {
    int spi_fd = -1;
    uint8_t spi_mode = 0;
    uint8_t spi_bits_per_word = 8;
    uint32_t spi_speed_hz = 1125000; // 1.125MHz
    uint8_t tx_buffer[BUFFER_SIZE] = {0};
    uint8_t rx_buffer[BUFFER_SIZE] = {0};
    struct spi_ioc_transfer spi_transfer = {0};

    // Open the SPI device
    spi_fd = open(SPI_DEVICE, O_RDWR);
    if (spi_fd < 0) {
        printf("Failed to open SPI device\\\\n");
        return -1;
    }

    // Set SPI mode
    if (ioctl(spi_fd, SPI_IOC_WR_MODE, &spi_mode) < 0) {
        printf("Failed to set SPI mode\\\\n");
        close(spi_fd);
        return -1;
    }

    // Set SPI bits per word
    if (ioctl(spi_fd, SPI_IOC_WR_BITS_PER_WORD, &spi_bits_per_word) < 0) {
        printf("Failed to set SPI bits per word\\\\n");
        close(spi_fd);
        return -1;
    }

    // Set SPI speed
    if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi_speed_hz) < 0) {
        printf("Failed to set SPI speed\\\\n");
        close(spi_fd);
        return -1;
    }

    // Set transfer parameters
    spi_transfer.tx_buf = (unsigned long)tx_buffer;
    spi_transfer.rx_buf = (unsigned long)rx_buffer;
    spi_transfer.len = BUFFER_SIZE;
    spi_transfer.delay_usecs = 0;
    spi_transfer.speed_hz = spi_speed_hz;
    spi_transfer.bits_per_word = spi_bits_per_word;
    spi_transfer.cs_change = 0;

    // Send the SPI message
    if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &spi_transfer) < 0) {
        printf("Failed to send SPI message\\\\n");
        close(spi_fd);
        return -1;
    }

    // Print received data
    printf("Received data:\n");
    printf("%s",rx_buffer);
    // Close the SPI device
    close(spi_fd);

    return 0;
}

