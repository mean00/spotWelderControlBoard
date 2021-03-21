
SET(SRCS 
                DefaultFonts.c  
                ssd1306_i2c.cpp
                ssd1306_ex.cpp
                ssd1306_i2c_f1.cpp
        )
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
generate_arduino_library(${libPrefix}ssd1306 
                            SRCS ${SRCS}
                            BOARD ${ARDUINO_DEFAULT_BOARD}
                        )
