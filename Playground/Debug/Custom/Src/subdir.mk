################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Custom/Src/led_control_task.c 

OBJS += \
./Custom/Src/led_control_task.o 

C_DEPS += \
./Custom/Src/led_control_task.d 


# Each subdirectory must supply rules for building sources it contributes
Custom/Src/%.o Custom/Src/%.su Custom/Src/%.cyclo: ../Custom/Src/%.c Custom/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../USB_HOST/App -I../USB_HOST/Target -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Host_Library/Class/CDC/Inc -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Practice/Denys-Projects/Playground/Playground/Custom/Inc" -include"C:/Practice/Denys-Projects/Playground/Playground/Custom/Inc/led_control_task.h" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Custom-2f-Src

clean-Custom-2f-Src:
	-$(RM) ./Custom/Src/led_control_task.cyclo ./Custom/Src/led_control_task.d ./Custom/Src/led_control_task.o ./Custom/Src/led_control_task.su

.PHONY: clean-Custom-2f-Src

