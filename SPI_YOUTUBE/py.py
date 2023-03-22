import spidev

# Open SPI bus 0, device 0
spi = spidev.SpiDev()
spi.open(0, 0)

# Set SPI mode and speed
spi.mode = 0
spi.max_speed_hz = 11250000

# Define a function to receive and print SPI data
def receive_and_print_spi_data():
    while True:
        # Create a buffer to receive the data
        buffer_size = 10
        buffer = [0] * buffer_size

        # Receive the data over SPI
        for i in range(buffer_size):
            buffer[i] = spi.xfer2([0])[0]

        # Print the received data
        print("Received data:", buffer)

# Call the receive_and_print_spi_data functionf
receive_and_print_spi_data()

# Close the SPI bus (this line will never be executed)
spi.close()
