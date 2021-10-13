################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/interrupts.c \
../src/main_loop.c \
../src/platform.c \
../src/sevenSeg_new.c 

OBJS += \
./src/interrupts.o \
./src/main_loop.o \
./src/platform.o \
./src/sevenSeg_new.o 

C_DEPS += \
./src/interrupts.d \
./src/main_loop.d \
./src/platform.d \
./src/sevenSeg_new.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MicroBlaze gcc compiler'
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../Lab_1b_Stopwatch_bsp/microblaze_0/include -mlittle-endian -mxl-barrel-shift -mcpu=v11.0 -mno-xl-soft-mul -Wl,--no-relax -ffunction-sections -fdata-sections -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


