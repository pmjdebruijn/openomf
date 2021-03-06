
SET(MODPLUG_SEARCH_PATHS
    /usr/local/
    /usr
    /opt
)

FIND_PATH(MODPLUG_INCLUDE_DIR libmodplug/modplug.h
    HINTS ${MODPLUG_ROOT}
    PATH_SUFFIXES include
    PATHS ${MODPLUG_SEARCH_PATHS}
)
FIND_LIBRARY(MODPLUG_LIBRARY modplug
    HINTS ${MODPLUG_ROOT}
    PATH_SUFFIXES lib64 lib
    PATHS ${MODPLUG_SEARCH_PATHS}
)

IF(MODPLUG_INCLUDE_DIR AND MODPLUG_LIBRARY)
   SET(MODPLUG_FOUND TRUE)
ENDIF()


IF(MODPLUG_FOUND)
    MESSAGE(STATUS "Found Modplug: ${MODPLUG_LIBRARY}")
ELSE()
    MESSAGE(WARNING "Could not find Modplug")
ENDIF()