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
  

USE_LIBRARY(RotaryEncoder)
USE_LIBRARY(WS2812B)

include_directories(assets)

SET(SSD1306 ${AF_FOLDER}/libraries/simplerSSD1306)
include_directories(${SSD1306})
SET(LIBSSD1306 ${SSD1306}/ssd1306_base.cpp ${SSD1306}/ssd1306_ex.cpp ${SSD1306}/ssd1306_i2c_lnGd32vf103.cpp)

ADD_LIBRARY(SSD1306 STATIC ${LIBSSD1306})
        
GENERATE_GD32_FIRMWARE(spotWelder
                        src/demo.cpp 
                        #src/rotary.cpp 
                        #src/dso_logger.cpp 
                        src/pulse.cpp
                        #src/dso_eeprom.cpp
                        src/dso_eeprom_stub.cpp
                        src/measurement.cpp
                        src/mainMenu.cpp
                        src/voltageCalibration.cpp
                        src/SSD1306.cpp
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
 
target_link_libraries(spotWelder SSD1306 RotaryEncoder WS2812B)
        
