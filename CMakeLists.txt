#-----------------------------------------------------------------------------
#
# CMAkeLists for DSO-STM32
# An opensource firmware for the DSO SHELL 150
# With optional hardware mods :
#   - Alterntive rotary encoder wiring : MUCH Better, almost mandatory
#   - Use GD32F303 as another MCU (much faster, better ADC, more memory)
#
#-----------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(select_mcu_stm32)
include(applyPatch)
# Patch Arduino_stm32 if needed to add gd32f303 support
#
ADD_DEFINITIONS(-DHWIRE=Wire)
include(./platformConfig.cmake)
APPLY_PATCH_IF_NEEDED(patched gd32_patch.diff              "add gd32f303 support") 
APPLY_PATCH_IF_NEEDED(patchedm4 m4_activate_fpu.diff       "activate m4 fpu (gd32f303)") 

include_directories(Arduino_STM32/STM32F1/libraries/Wire/)
include_directories(oled)
cmake_minimum_required(VERSION 2.8)
#
SET(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)
Project("dso_stm32" C CXX ASM)

set(ARDUINO_DEFAULT_BOARD ${X_ARDUINO_DEFAULT_BOARD})        # Default Board ID, when not specified
set(ARDUINO_CPU           ${X_ARDUINO_CPU})
SET(ARDUINO_UPLOAD_METHOD ${X_ARDUINO_UPLOAD_METHOD}) # Use blackmagic link, if you comment it out you'll use DFU => 8kB flash
set(ARDUINO_DEFAULT_PORT ttyACM0) # Default Port, when not specified


SET(libPrefix ${ARDUINO_DEFAULT_BOARD}_)


MESSAGE(STATUS "Starting dso-stm32")
SET(EXTENSION "${EXTENSION}_${MCU_SPEED_M}M")

 
 
include_directories(MapleFreeRTOS1000//Source/include)
include_directories(MapleFreeRTOS1000//)
include_directories(.)
include_directories(adc)
include_directories(src)

# FreeRTOS
# Other modules
ADD_SUBDIRECTORY(adc) 
ADD_SUBDIRECTORY(MapleFreeRTOS1000/)
#
generate_arduino_firmware(Oled${EXTENSION} 
                SKETCH OLED_I2C_3D_Cube.ino
                SRCS    demo.cpp oled/DefaultFonts.c oled/OLED_I2C.cpp  embedded_printf/printf.c  rotary.cpp stubs/usb_stubs.cpp src/dso_logger.cpp
                PORT ${ARDUINO_DEFAULT_PORT}
                BOARD_CPU ${ARDUINO_CPU}
                )
TARGET_LINK_LIBRARIES( Oled${EXTENSION}  ${libPrefix}FreeRTOS)
TARGET_LINK_LIBRARIES( Oled${EXTENSION}  ${libPrefix}adc)
#TARGET_LINK_LIBRARIES( Oled${EXTENSION}  ${libPrefix}tests)


# Summary
MESSAGE(STATUS "Configuration:")
#
MESSAGE(STATUS "\tUsing ${EXTENSION} MCU at ${MCU_SPEED} Hz")
