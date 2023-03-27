#include <pigpio.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#define I2C_ADDRESS 0x10
#define UART_BAUD_RATE 115200
#define SPI_CHANNEL 0
#define SPI_SPEED 1125000

void sendDataUart(int uart_fd);
void receiveDataI2C(int i2c_fd);
void sendSpiData(int spi_fd);
void receiveDataUart(int uart_fd);
void sendDataI2C(int i2c_fd);
void receiveSpiData(int spi_fd);

int main() {
  // Initialize pigpio
  if (gpioInitialise() < 0) {
    fprintf(stderr, "pigpio initialisation failed\n");
    return 1;
  }

  // UART setup
  int uart_fd = serOpen("/dev/ttyS0", UART_BAUD_RATE, 0);
  if (uart_fd < 0) {
    fprintf(stderr, "UART open failed\n");
    gpioTerminate();
    return 1;
  }

  // I2C setup
  int i2c_fd = i2cOpen(1, I2C_ADDRESS, 0);
  if (i2c_fd < 0) {
    fprintf(stderr, "I2C open failed\n");
    serClose(uart_fd);
    gpioTerminate();
    return 1;
  }

  // SPI setup
  int spi_fd = spiOpen(SPI_CHANNEL, SPI_SPEED, 0);
  if (spi_fd < 0) {
    fprintf(stderr, "SPI open failed\n");
    i2cClose(i2c_fd);
    serClose(uart_fd);
    gpioTerminate();
    return 1;
  }

  while (1) {
    receiveDataUart(uart_fd);
    sendDataI2C(i2c_fd);
    receiveSpiData(spi_fd);
  }

  serClose(uart_fd);
  i2cClose(i2c_fd);
  spiClose(spi_fd);
  gpioTerminate();
  return 0;
}

void sendDataUart(int uart_fd) {
  const char *data = "Hello, UART!";
  int result = serWrite(uart_fd, data, strlen(data));
  if (result < 0) {
    fprintf(stderr, "UART write failed\n");
  }
  usleep(1000000);
}

void receiveDataI2C(int i2c_fd) {
  uint8_t received_data;
  int result = i2cReadDevice(i2c_fd, &received_data, 1);
  if (result < 0) {
    fprintf(stderr, "I2C read failed\n");
  } else {
    printf("I2C Received: %02X\n", received_data);
  }
  usleep(1000000);
}

void sendSpiData(int spi_fd) {
  uint8_t data_to_send = 0xAB;
  int result = spiWrite(spi_fd, &data_to_send, 1);
  if (result < 0) {
    fprintf(stderr, "SPI write failed\n");
  }
  usleep(1000000);
}

void receiveDataUart(int uart_fd) {
  if (serDataAvailable(uart_fd)) {
    char received_data[50] ={0};
    int result = serRead(uart_fd, received_data, sizeof(received_data));
    if (result < 0) {
      fprintf(stderr, "UART read failed\n");
    } else {
      printf("UART Received: %s\n", received_data);
      fwrite(received_data, 1, sizeof(received_data), stdout);
    }
  }
}

void sendDataI2C(int i2c_fd) {
  //uint8_t data_to_send = 0x55;
  //uint8_t *data_to_send_v2 = "i am data i2c";
  char data_to_send_v2[50]={0};
  int len = snprintf(data_to_send_v2, 50, "i am data buffer from pi4b \n");
  //i2cWriteDevice(i2c_fd, &data_to_send, 1);
  i2cWriteDevice(i2c_fd, &data_to_send_v2, 1);
  //printf("I2C Sent: %02X\n", data_to_send);
  printf("I2C Sent: %s\n", data_to_send_v2);

  usleep(1000000);
}

void receiveSpiData(int spi_fd) {
  uint8_t rx_buffer[50] = {0};
  //uint8_t data_received;
  spiRead(spi_fd, &rx_buffer, 50);
  //printf("SPI Received: %02X\n", data_received);
  printf("SPI Received: %s\n",rx_buffer);
  usleep(1000000);
}

