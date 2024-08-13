################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
../Sources/DSP2833x_ADC_cal.asm \
../Sources/DSP2833x_CSMPasswords.asm \
../Sources/DSP2833x_CodeStartBranch.asm \
../Sources/DSP2833x_DBGIER.asm \
../Sources/DSP2833x_DisInt.asm \
../Sources/DSP2833x_usDelay.asm 

C_SRCS += \
../Sources/CRC.c \
../Sources/DSP2833x_Adc.c \
../Sources/DSP2833x_CpuTimers.c \
../Sources/DSP2833x_DMA.c \
../Sources/DSP2833x_DefaultIsr.c \
../Sources/DSP2833x_ECan.c \
../Sources/DSP2833x_ECap.c \
../Sources/DSP2833x_EPwm.c \
../Sources/DSP2833x_EQep.c \
../Sources/DSP2833x_GlobalVariableDefs.c \
../Sources/DSP2833x_Gpio.c \
../Sources/DSP2833x_I2C.c \
../Sources/DSP2833x_Mcbsp.c \
../Sources/DSP2833x_MemCopy.c \
../Sources/DSP2833x_PieCtrl.c \
../Sources/DSP2833x_PieVect.c \
../Sources/DSP2833x_Sci.c \
../Sources/DSP2833x_Spi.c \
../Sources/DSP2833x_SysCtrl.c \
../Sources/DSP2833x_Xintf.c \
../Sources/Flash.c \
../Sources/Protocole.c \
../Sources/SPI.c \
../Sources/sci.c 

C_DEPS += \
./Sources/CRC.d \
./Sources/DSP2833x_Adc.d \
./Sources/DSP2833x_CpuTimers.d \
./Sources/DSP2833x_DMA.d \
./Sources/DSP2833x_DefaultIsr.d \
./Sources/DSP2833x_ECan.d \
./Sources/DSP2833x_ECap.d \
./Sources/DSP2833x_EPwm.d \
./Sources/DSP2833x_EQep.d \
./Sources/DSP2833x_GlobalVariableDefs.d \
./Sources/DSP2833x_Gpio.d \
./Sources/DSP2833x_I2C.d \
./Sources/DSP2833x_Mcbsp.d \
./Sources/DSP2833x_MemCopy.d \
./Sources/DSP2833x_PieCtrl.d \
./Sources/DSP2833x_PieVect.d \
./Sources/DSP2833x_Sci.d \
./Sources/DSP2833x_Spi.d \
./Sources/DSP2833x_SysCtrl.d \
./Sources/DSP2833x_Xintf.d \
./Sources/Flash.d \
./Sources/Protocole.d \
./Sources/SPI.d \
./Sources/sci.d 

OBJS += \
./Sources/CRC.obj \
./Sources/DSP2833x_ADC_cal.obj \
./Sources/DSP2833x_Adc.obj \
./Sources/DSP2833x_CSMPasswords.obj \
./Sources/DSP2833x_CodeStartBranch.obj \
./Sources/DSP2833x_CpuTimers.obj \
./Sources/DSP2833x_DBGIER.obj \
./Sources/DSP2833x_DMA.obj \
./Sources/DSP2833x_DefaultIsr.obj \
./Sources/DSP2833x_DisInt.obj \
./Sources/DSP2833x_ECan.obj \
./Sources/DSP2833x_ECap.obj \
./Sources/DSP2833x_EPwm.obj \
./Sources/DSP2833x_EQep.obj \
./Sources/DSP2833x_GlobalVariableDefs.obj \
./Sources/DSP2833x_Gpio.obj \
./Sources/DSP2833x_I2C.obj \
./Sources/DSP2833x_Mcbsp.obj \
./Sources/DSP2833x_MemCopy.obj \
./Sources/DSP2833x_PieCtrl.obj \
./Sources/DSP2833x_PieVect.obj \
./Sources/DSP2833x_Sci.obj \
./Sources/DSP2833x_Spi.obj \
./Sources/DSP2833x_SysCtrl.obj \
./Sources/DSP2833x_Xintf.obj \
./Sources/DSP2833x_usDelay.obj \
./Sources/Flash.obj \
./Sources/Protocole.obj \
./Sources/SPI.obj \
./Sources/sci.obj 

ASM_DEPS += \
./Sources/DSP2833x_ADC_cal.d \
./Sources/DSP2833x_CSMPasswords.d \
./Sources/DSP2833x_CodeStartBranch.d \
./Sources/DSP2833x_DBGIER.d \
./Sources/DSP2833x_DisInt.d \
./Sources/DSP2833x_usDelay.d 

OBJS__QUOTED += \
"Sources\CRC.obj" \
"Sources\DSP2833x_ADC_cal.obj" \
"Sources\DSP2833x_Adc.obj" \
"Sources\DSP2833x_CSMPasswords.obj" \
"Sources\DSP2833x_CodeStartBranch.obj" \
"Sources\DSP2833x_CpuTimers.obj" \
"Sources\DSP2833x_DBGIER.obj" \
"Sources\DSP2833x_DMA.obj" \
"Sources\DSP2833x_DefaultIsr.obj" \
"Sources\DSP2833x_DisInt.obj" \
"Sources\DSP2833x_ECan.obj" \
"Sources\DSP2833x_ECap.obj" \
"Sources\DSP2833x_EPwm.obj" \
"Sources\DSP2833x_EQep.obj" \
"Sources\DSP2833x_GlobalVariableDefs.obj" \
"Sources\DSP2833x_Gpio.obj" \
"Sources\DSP2833x_I2C.obj" \
"Sources\DSP2833x_Mcbsp.obj" \
"Sources\DSP2833x_MemCopy.obj" \
"Sources\DSP2833x_PieCtrl.obj" \
"Sources\DSP2833x_PieVect.obj" \
"Sources\DSP2833x_Sci.obj" \
"Sources\DSP2833x_Spi.obj" \
"Sources\DSP2833x_SysCtrl.obj" \
"Sources\DSP2833x_Xintf.obj" \
"Sources\DSP2833x_usDelay.obj" \
"Sources\Flash.obj" \
"Sources\Protocole.obj" \
"Sources\SPI.obj" \
"Sources\sci.obj" 

C_DEPS__QUOTED += \
"Sources\CRC.d" \
"Sources\DSP2833x_Adc.d" \
"Sources\DSP2833x_CpuTimers.d" \
"Sources\DSP2833x_DMA.d" \
"Sources\DSP2833x_DefaultIsr.d" \
"Sources\DSP2833x_ECan.d" \
"Sources\DSP2833x_ECap.d" \
"Sources\DSP2833x_EPwm.d" \
"Sources\DSP2833x_EQep.d" \
"Sources\DSP2833x_GlobalVariableDefs.d" \
"Sources\DSP2833x_Gpio.d" \
"Sources\DSP2833x_I2C.d" \
"Sources\DSP2833x_Mcbsp.d" \
"Sources\DSP2833x_MemCopy.d" \
"Sources\DSP2833x_PieCtrl.d" \
"Sources\DSP2833x_PieVect.d" \
"Sources\DSP2833x_Sci.d" \
"Sources\DSP2833x_Spi.d" \
"Sources\DSP2833x_SysCtrl.d" \
"Sources\DSP2833x_Xintf.d" \
"Sources\Flash.d" \
"Sources\Protocole.d" \
"Sources\SPI.d" \
"Sources\sci.d" 

ASM_DEPS__QUOTED += \
"Sources\DSP2833x_ADC_cal.d" \
"Sources\DSP2833x_CSMPasswords.d" \
"Sources\DSP2833x_CodeStartBranch.d" \
"Sources\DSP2833x_DBGIER.d" \
"Sources\DSP2833x_DisInt.d" \
"Sources\DSP2833x_usDelay.d" 

C_SRCS__QUOTED += \
"../Sources/CRC.c" \
"../Sources/DSP2833x_Adc.c" \
"../Sources/DSP2833x_CpuTimers.c" \
"../Sources/DSP2833x_DMA.c" \
"../Sources/DSP2833x_DefaultIsr.c" \
"../Sources/DSP2833x_ECan.c" \
"../Sources/DSP2833x_ECap.c" \
"../Sources/DSP2833x_EPwm.c" \
"../Sources/DSP2833x_EQep.c" \
"../Sources/DSP2833x_GlobalVariableDefs.c" \
"../Sources/DSP2833x_Gpio.c" \
"../Sources/DSP2833x_I2C.c" \
"../Sources/DSP2833x_Mcbsp.c" \
"../Sources/DSP2833x_MemCopy.c" \
"../Sources/DSP2833x_PieCtrl.c" \
"../Sources/DSP2833x_PieVect.c" \
"../Sources/DSP2833x_Sci.c" \
"../Sources/DSP2833x_Spi.c" \
"../Sources/DSP2833x_SysCtrl.c" \
"../Sources/DSP2833x_Xintf.c" \
"../Sources/Flash.c" \
"../Sources/Protocole.c" \
"../Sources/SPI.c" \
"../Sources/sci.c" 

ASM_SRCS__QUOTED += \
"../Sources/DSP2833x_ADC_cal.asm" \
"../Sources/DSP2833x_CSMPasswords.asm" \
"../Sources/DSP2833x_CodeStartBranch.asm" \
"../Sources/DSP2833x_DBGIER.asm" \
"../Sources/DSP2833x_DisInt.asm" \
"../Sources/DSP2833x_usDelay.asm" 


