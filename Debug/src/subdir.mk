################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/HelloWorldApp.cpp 

OBJS += \
./src/HelloWorldApp.o 

CPP_DEPS += \
./src/HelloWorldApp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/Users/asaeed/code/cinder/cinder_master/boost -I/Users/asaeed/code/cinder/cinder_master/include -I"/Users/asaeed/Dropbox/code/cinderMac/ocvBlob/thirdparty" -I"/Users/asaeed/Dropbox/code/cinderMac/ocvBlob/include" -I/System/Library/Frameworks/OpenGL.framework/Headers -I"/Users/asaeed/code/cinder/cinder_master/blocks/opencv/include" -O0 -g -Wall -c -fmessage-length=0 -arch i386 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


