import smbus
import time

# Set up the I2C bus and the device address
bus = smbus.SMBus(1)  # Use 1 for Raspberry Pi 4B, 0 for older models
device_address = 10  # STM32F746ZG I2C device address

# Define a buffer to send
buffer = [0x01, 0x02, 0x03, 0x04]

def send_i2c_buffer(device_address, buffer):
    try:
        # Write the buffer to the I2C device
        bus.write_i2c_block_data(device_address, 0, buffer)
        print("Sent buffer:", buffer)
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    send_i2c_buffer(device_address, buffer)
