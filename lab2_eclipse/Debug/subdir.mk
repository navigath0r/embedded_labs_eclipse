################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CardReader.cpp \
../main.cpp 

OBJS += \
./CardReader.o \
./main.o 

CPP_DEPS += \
./CardReader.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	arm-xilinx-linux-gnueabi-g++ -std=c++0x -O0 -g -Wall -c -fmessage-length=0 -ggdb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


