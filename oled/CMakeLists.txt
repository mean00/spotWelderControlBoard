
SET(SRCS 
                DefaultFonts.c  ssd1306_i2c.cpp
        )
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
generate_arduino_library(${libPrefix}ssd1306 
                            SRCS ${SRCS}
                            BOARD ${ARDUINO_DEFAULT_BOARD}
                        )
