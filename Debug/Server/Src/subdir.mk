################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Server/Src/I2c.c \
../Server/Src/Server_Main.c \
../Server/Src/Spi.c \
../Server/Src/Tools.c \
../Server/Src/Uart.c 

OBJS += \
./Server/Src/I2c.o \
./Server/Src/Server_Main.o \
./Server/Src/Spi.o \
./Server/Src/Tools.o \
./Server/Src/Uart.o 

C_DEPS += \
./Server/Src/I2c.d \
./Server/Src/Server_Main.d \
./Server/Src/Spi.d \
./Server/Src/Tools.d \
./Server/Src/Uart.d 


# Each subdirectory must supply rules for building sources it contributes
Server/Src/%.o Server/Src/%.su: ../Server/Src/%.c Server/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../LWIP/App -I../LWIP/Target -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/system -I../Drivers/BSP/Components/lan8742 -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/Third_Party/LwIP/src/include/netif -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Middlewares/Third_Party/LwIP/system/arch -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Server-2f-Src

clean-Server-2f-Src:
	-$(RM) ./Server/Src/I2c.d ./Server/Src/I2c.o ./Server/Src/I2c.su ./Server/Src/Server_Main.d ./Server/Src/Server_Main.o ./Server/Src/Server_Main.su ./Server/Src/Spi.d ./Server/Src/Spi.o ./Server/Src/Spi.su ./Server/Src/Tools.d ./Server/Src/Tools.o ./Server/Src/Tools.su ./Server/Src/Uart.d ./Server/Src/Uart.o ./Server/Src/Uart.su

.PHONY: clean-Server-2f-Src

