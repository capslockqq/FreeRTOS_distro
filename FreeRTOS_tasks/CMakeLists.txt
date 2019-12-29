#####################################################################
# simple AVR library
#####################################################################
file(GLOB FreeRTOS_Tasks_src
    "*.cpp"
    "*.hpp"
)
if(BUILD_TYPE STREQUAL "TARGET")
    add_avr_library(
    Free_RTOS_Tasks
    ${FreeRTOS_Tasks_src}
    )
else()
    add_library (
        pc-Free_RTOS_Tasks
        ${FreeRTOS_Tasks_src}
    )
endif()
