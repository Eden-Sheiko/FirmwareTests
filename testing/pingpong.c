#include <pigpio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include "pingpong.h"

packet_t packet = {ZERO};


int main()
{
  uint8_t struct_size = sizeof(packet);
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
  // mutexs

  // CON VAR

  // starting the threads

  pthread_t uart_thread;
  pthread_t i2c_thread;
  pthread_t spi_thread;
  pthread_t udp_thread;

  int ret1 = pthread_create(&uart_thread, NULL, &func_uart, (void *)(intptr_t)uart_fd);
  if (ret1 != ZERO)
  {
    perror("Failed to create thread_uart \n");
    return 1;
  }
  int ret2 = pthread_create(&i2c_thread, NULL, &func_i2c, (void *)(intptr_t)i2c_fd);
  if (ret2 != ZERO)
  {
    perror("Failed to create thread_i2c \n");
    pthread_cancel(uart_thread);
    return 1;
  }
  int ret3 = pthread_create(&spi_thread, NULL, &func_spi, (void *)(intptr_t)spi_fd);
  if (ret3 != ZERO)
  {
    perror("Failed to create thread_spi \n");
    pthread_cancel(uart_thread);
    pthread_cancel(i2c_thread);
    return 1;
  }
  int ret4 = pthread_create(&uart_thread, NULL, &func_udp, (void *)(intptr_t)uart_fd);
  if (ret4 != ZERO)
  {
    perror("Failed to create thread_udp \n");
    pthread_cancel(uart_thread);
    pthread_cancel(i2c_thread);
    pthread_cancel(spi_thread);
    return 1;
  }

  while (TRUE)
  {
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
  // usleep(DELAY_TIME);
}

void receiveDataI2C(int i2c_fd)
{
  uint8_t received_data;
  i2cReadDevice(i2c_fd, &received_data, 1);
  printf("I2C Received: %02X\n", received_data);
  // usleep(DELAY_TIME);
}

void sendSpiData(int spi_fd)
{
  uint8_t data_to_send = 0xAB;
  spiWrite(spi_fd, &data_to_send, 1);
  // usleep(DELAY_TIME);
}

void receiveDataUart(int uart_fd)
{
  if (serDataAvailable(uart_fd))
  {
    int byte_rev = serRead(uart_fd, (char*)packet.data, sizeof(packet.data));
    if (byte_rev < ZERO)
    {
      fprintf(stderr, "Error reading UART\n");
    }
    else if (byte_rev > ZERO)
    {
      printf("UART Received string: %s\n", packet.data);
      fwrite(packet.data, 1, sizeof(packet.data), stdout);
    }
  }
}

void sendDataI2C(int i2c_fd)
{
  // uint8_t data_to_send = 0x55;
  // uint8_t *data_to_send_v2 = "i am data i2c";
  char data_to_send_v2[BUFF_SIZE] = {ZERO};
  int len = snprintf(data_to_send_v2, 50, "i am data buffer from pi4b \n");
  // i2cWriteDevice(i2c_fd, &data_to_send, 1);
  i2cWriteDevice(i2c_fd, &data_to_send_v2, 1);
  // printf("I2C Sent: %02X\n", data_to_send);
  printf("I2C Sent: %s\n", data_to_send_v2);

  // usleep(DELAY_TIME);
}

void receiveSpiData(int spi_fd)
{
  uint8_t rx_buffer[BUFF_SIZE] = {ZERO};
  spiRead(spi_fd, &rx_buffer, 15);
  printf("SPI Received: %s\n", rx_buffer);
  // usleep(DELAY_TIME);
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

void *func_uart(void *arg)
{

  printf("Inside the thread uart\n");
  while (TRUE)
  {

    int uart_fd = (int)(intptr_t)arg;

    receiveDataUart(uart_fd);
    usleep(SHORT_DELAY);
  }

  // exit the current thread
  // pthread_exit(NULL);
}

void *func_i2c(void *arg)
{

  printf("Inside the thread i2c\n");
  // while (TRUE)
  // {

  //   int i2c_fd = (int)(intptr_t)arg;

  //   sendDataI2C(i2c_fd);
  //   usleep(SHORT_DELAY);
  // }

  // exit the current thread
  // pthread_exit(NULL);
}

void *func_spi(void *arg)
{

  printf("Inside the thread spi\n");
  // while (TRUE)
  // {

  //   int spi_fd = (int)(intptr_t)arg;

  //   receiveSpiData(spi_fd);
  //   usleep(SHORT_DELAY);
  // }
  // exit the current thread
  // pthread_exit(NULL);
}

void *func_udp(void *arg)
{

  printf("Inside the thread udp\n");

  // while (TRUE)
  // {

  //   // work here!
  // }
  // exit the current thread
  // pthread_exit(NULL);
}
