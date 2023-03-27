#if !defined(PINGPING_H)
#define PINGPING_H
#define I2C_ADDRESS 0x10
#define UART_BAUD_RATE 115200
#define SPI_CHANNEL 0
#define SPI_SPEED 1125000

//private defines
#define TRUE 1
#define FALSE 0
//--------------//
#define ZERO 0
#define FAIL -1
//--------------//
#define DELAY_TIME 1000000

// threads functions
void* func_uart(void* arg);
void* func_i2c(void* arg);
void* func_spi(void* arg);

// send and receive function
void sendDataUart(int uart_fd);
void receiveDataI2C(int i2c_fd);
void sendSpiData(int spi_fd);
void receiveDataUart(int uart_fd);
void sendDataI2C(int i2c_fd);
void receiveSpiData(int spi_fd);

// setup function for the communication protocols

int setupUart();
int setupI2c();
int setupSpi();
#endif // PINGPING_H
