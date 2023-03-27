#include <pigpio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include "pingpong.h"

int main()
{
  // Initialize pigpio
  if (gpioInitialise() < ZERO)
  {
    fprintf(stderr, "pigpio initialisation failed\n");
    return 1;
  }

  // UART setup
  int uart_fd = setupUart();
  if (uart_fd < ZERO)
  {
    serClose(uart_fd);
    gpioTerminate();
    return -1;
  }

  // I2C setup
  int i2c_fd = setupI2c();
  if (i2c_fd < ZERO)
  {
    serClose(uart_fd);
    i2cClose(i2c_fd);
    gpioTerminate();
    return -1;
  }

  // SPI setup
  int spi_fd = setupSpi();
  if (spi_fd < ZERO)
  {
    serClose(uart_fd);
    i2cClose(i2c_fd);
    spiClose(spi_fd);
    gpioTerminate();
    return -1;
  }

  // starting the threads

  pthread_t uart_thread;
  pthread_t i2c_thread;
  pthread_t spi_thread;
  //pthread_t udp_thread;

  pthread_create(&uart_thread, NULL, &func_uart, NULL);
  pthread_create(&i2c_thread, NULL, &func_i2c, NULL);
  pthread_create(&spi_thread, NULL, &func_spi, NULL);



  while (TRUE)
  {
   

    // by the datasheet

    // UART
    receiveDataUart(uart_fd);
    usleep(DELAY_TIME);


    // I2C
    sendDataI2C(i2c_fd);
    usleep(DELAY_TIME);


    // SPI
    receiveSpiData(spi_fd);
    usleep(DELAY_TIME);
  
  }

  serClose(uart_fd);
  i2cClose(i2c_fd);
  spiClose(spi_fd);
  gpioTerminate();
  return ZERO;
}

void sendDataUart(int uart_fd)
{
  const char *data = "Hello, UART!";
  serWrite(uart_fd, data, strlen(data));
  //usleep(DELAY_TIME);
}

void receiveDataI2C(int i2c_fd)
{
  uint8_t received_data;
  i2cReadDevice(i2c_fd, &received_data, 1);
  printf("I2C Received: %02X\n", received_data);
  //usleep(DELAY_TIME);
}

void sendSpiData(int spi_fd)
{
  uint8_t data_to_send = 0xAB;
  spiWrite(spi_fd, &data_to_send, 1);
  //usleep(DELAY_TIME);
}

void receiveDataUart(int uart_fd)
{
  if (serDataAvailable(uart_fd))
  {
    char received_data[50] = {ZERO};
    serRead(uart_fd, received_data, sizeof(received_data));
    printf("UART Received: %s\n", received_data);
    fwrite(received_data, 1, sizeof(received_data), stdout);
  }
}

void sendDataI2C(int i2c_fd)
{
  // uint8_t data_to_send = 0x55;
  // uint8_t *data_to_send_v2 = "i am data i2c";
  char data_to_send_v2[50] = {ZERO};
  int len = snprintf(data_to_send_v2, 50, "i am data buffer from pi4b \n");
  // i2cWriteDevice(i2c_fd, &data_to_send, 1);
  i2cWriteDevice(i2c_fd, &data_to_send_v2, 1);
  // printf("I2C Sent: %02X\n", data_to_send);
  printf("I2C Sent: %s\n", data_to_send_v2);

  //usleep(DELAY_TIME);
}

void receiveSpiData(int spi_fd)
{
  uint8_t rx_buffer[50] = {ZERO};
  // uint8_t data_received;
  spiRead(spi_fd, &rx_buffer, 50);
  // printf("SPI Received: %02X\n", data_received);
  printf("SPI Received: %s\n", rx_buffer);
  //usleep(DELAY_TIME);
}

int setupUart()
{
  int uart_fd = serOpen("/dev/ttyS0", UART_BAUD_RATE, 0);
  return (uart_fd > ZERO) ? TRUE : FALSE;
}
int setupI2c()
{
  int i2c_fd = i2cOpen(1, I2C_ADDRESS, 0);
  return (i2c_fd > ZERO) ? TRUE : FALSE;
}
int setupSpi()
{
  int spi_fd = spiOpen(SPI_CHANNEL, SPI_SPEED, 0);
  return (spi_fd > ZERO) ? TRUE : FALSE;
}


void* func_uart(void* arg)
{
    // detach the current thread
    // from the calling thread
    pthread_detach(pthread_self());
  
    printf("Inside the thread\n");
  
    // exit the current thread
    pthread_exit(NULL);
}

void* func_i2c(void* arg)
{
    // detach the current thread
    // from the calling thread
    pthread_detach(pthread_self());
  
    printf("Inside the thread\n");
  
    // exit the current thread
    pthread_exit(NULL);
}

void* func_spi(void* arg)
{
    // detach the current thread
    // from the calling thread
    pthread_detach(pthread_self());
  
    printf("Inside the thread\n");
  
    // exit the current thread
    pthread_exit(NULL);
}
