#####################################################################
# simple AVR library
#####################################################################
file(GLOB FreeRTOS_Linux_src
    "*.c"
    "portable/*.c"
    "*.h"
    "portable/*.h"

)
if(BUILD_TYPE STREQUAL "TARGET")
else()
    add_library (
        Free_RTOS_Linux
        ${FreeRTOS_Linux_src}
    )
endif()
