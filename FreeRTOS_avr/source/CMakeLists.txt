#####################################################################
# simple AVR library
#####################################################################
file(GLOB FreeRTOS_src
    "*.c"
    "portable/*.c"
)
if(BUILD_TYPE STREQUAL "TARGET")
    add_avr_library(
    Free_RTOS
    ${FreeRTOS_src}
    )
else()
    add_library (
        Free_RTOS
        ${FreeRTOS_src}
    )
endif()
