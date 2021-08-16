IF(NOT DEFINED LN_ARCH)
IF(1)
    SET(LN_ARCH "ARM" CACHE INTERNAL "")
    SET(LN_MCU  "M3" CACHE INTERNAL "")
    SET(LN_MCU_FLASH_SIZE  64 CACHE INTERNAL "")
    SET(LN_MCU_RAM_SIZE    20 CACHE INTERNAL "")
    SET(LN_MCU_EEPROM_SIZE 2 CACHE INTERNAL "")
# To use spare broken GD32F1
    SET(LN_USE_INTERNAL_CLOCK True CACHE INTERNAL "") # No need for external crystal
    SET(LN_MCU_SPEED 36000000 True CACHE INTERNAL "")
ELSE()
    SET(LN_ARCH "RISCV" CACHE INTERNAL "")
    SET(LN_MCU  "VF103" CACHE INTERNAL "")
ENDIF()
ENDIF(NOT DEFINED LN_ARCH)
MESSAGE(STATUS "Architecture ${LN_ARCH}, MCU=${LN_MCU}")
