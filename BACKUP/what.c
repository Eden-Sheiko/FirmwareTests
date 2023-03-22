#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define SPI_DEVICE "/dev/spidev0.0"
#define SPI_MODE 0
#define SPI_SPEED_HZ 11250000
#define BUFFER_SIZE 16

int main(void) {
  int spi_fd;
  uint8_t tx_buffer[BUFFER_SIZE] = {0};
  uint8_t rx_buffer[BUFFER_SIZE] = {0};
  struct spi_ioc_transfer spi_xfer;

  spi_fd = open(SPI_DEVICE, O_RDWR);
  if (spi_fd < 0) {
    fprintf(stderr, "Failed to open SPI device\n");
    return 1;
  }

  // Set SPI mode
  if (ioctl(spi_fd, SPI_IOC_WR_MODE, SPI_MODE) < 0) {
    fprintf(stderr, "Failed to set SPI mode\n");
    close(spi_fd);
    return 1;
  }

  // Set SPI clock speed
  if (ioctl(spi_fd, SPI_IOC_WR_MAX_SPEED_HZ, SPI_SPEED_HZ) < 0) {
    fprintf(stderr, "Failed to set SPI clock speed\n");
    close(spi_fd);
    return 1;
  }

  // Clear buffers
  memset(tx_buffer, 0, BUFFER_SIZE);
  memset(rx_buffer, 0, BUFFER_SIZE);

  // Configure SPI transfer
  spi_xfer.tx_buf = (unsigned long)tx_buffer;
  spi_xfer.rx_buf = (unsigned long)rx_buffer;
  spi_xfer.len = BUFFER_SIZE;
  spi_xfer.delay_usecs = 0;
  spi_xfer.speed_hz = SPI_SPEED_HZ;
  spi_xfer.bits_per_word = 8;

  // Receive data from SPI device
  if (ioctl(spi_fd, SPI_IOC_MESSAGE(1), &spi_xfer) < 0) {
    fprintf(stderr, "Failed to receive data from SPI device\n");
    close(spi_fd);
    return 1;
  }

  // Print received data
  printf("Received data: ");
  for (int i = 0; i < BUFFER_SIZE; i++) {
    printf("%02X ", rx_buffer[i]);
  }
  printf("\n");

  // Close SPI connection
  close(spi_fd);

  return 0;
}
