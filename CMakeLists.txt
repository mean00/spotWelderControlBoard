#
#
#
#
SET(AF_FOLDER  ${CMAKE_SOURCE_DIR}/lnArduino CACHE INTERNAL "")
include(./mcuSelect.cmake)
SET(CMAKE_TOOLCHAIN_FILE ${AF_FOLDER}/lnArduino.cmake)
cmake_minimum_required(VERSION 3.0)


PROJECT(spotWelder C CXX ASM)

include_directories(${CMAKE_SOURCE_DIR})        
add_subdirectory(${AF_FOLDER})
include(${AF_FOLDER}/setup.cmake)
        
#SET(ST7735_DRIVER ${AF_FOLDER}/libraries/simplerST7735/platformExample/longanNano/gd32ST7735.cpp)
#include_directories(ST7735_DRIVER ${AF_FOLDER}/libraries/simplerST7735/platformExample/longanNano/)


#USE_LIBRARY(simplerST7735)
#USE_LIBRARY(RotaryEncoder)

include_directories(assets)
#add_subdirectory(assets)

GENERATE_GD32_FIRMWARE(spotWelder
                        src/demo.cpp 
                        #src/rotary.cpp 
                        #src/dso_logger.cpp 
                        src/pulse.cpp
                        #src/dso_eeprom.cpp
                        src/measurement.cpp
                        src/mainMenu.cpp
                        src/voltageCalibration.cpp
                        #src/SSD1306.cpp
                        src/buzzer.cpp
                        src/trigger.cpp
                        src/pulseWidth.cpp
                        src/goAuto.cpp
                        src/go.cpp
                        src/bench.cpp
                        src/pedal.cpp
                        src/goPedal.cpp
                        src/Leds.cpp
                        assets/assets.cpp
                        )
 
#target_link_libraries(spotWelder assets)
        
