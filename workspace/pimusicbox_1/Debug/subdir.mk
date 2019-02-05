################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fsm.c \
../kbhit.c \
../mfrc522.c \
../mfrc522_hal_linux.c \
../piMusicBox_1.c \
../rfid.c \
../tmr.c 

OBJS += \
./fsm.o \
./kbhit.o \
./mfrc522.o \
./mfrc522_hal_linux.o \
./piMusicBox_1.o \
./rfid.o \
./tmr.o 

C_DEPS += \
./fsm.d \
./kbhit.d \
./mfrc522.d \
./mfrc522_hal_linux.d \
./piMusicBox_1.d \
./rfid.d \
./tmr.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	arm-linux-gnueabihf-gcc -I"C:\SysGCC\Raspberry\include" -I"C:\SysGCC\Raspberry\include\wiringPi" -O0 -g3 -Wall -Werror -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


