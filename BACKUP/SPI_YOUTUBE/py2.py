import spidev
import time

# Open SPI bus
spi = spidev.SpiDev()
spi.open(0, 0)

# Disable chip select
spi.max_speed_hz = 11250000 # Set SPI clock frequency
spi.mode = 0b00 # Set SPI mode
spi.no_cs = True # Disable chip select

# Read data from SPI device
while True:
    data = spi.xfer2([0x00]*8) # Read 8 bytes of data
    print(data)
    time.sleep(1)

# Close SPI bus
spi.close()
