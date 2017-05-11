################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Connection.cpp \
../Main.cpp \
../Net.cpp \
../Neuron.cpp 

OBJS += \
./Connection.o \
./Main.o \
./Net.o \
./Neuron.o 

CPP_DEPS += \
./Connection.d \
./Main.d \
./Net.d \
./Neuron.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


