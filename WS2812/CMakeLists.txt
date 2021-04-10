
SET(SRCS WS2812B.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
generate_arduino_library(${libPrefix}WS2812 
                            SRCS ${SRCS}
                            BOARD ${ARDUINO_DEFAULT_BOARD}
                        )
