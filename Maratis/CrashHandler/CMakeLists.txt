## Find source and headers
FILE(GLOB_RECURSE HEADERS *.h)
FILE(GLOB_RECURSE SOURCES *.c*)

IF(CMAKE_HAS_SORT)
  LIST(SORT HEADERS)
  LIST(SORT SOURCES)
ENDIF(CMAKE_HAS_SORT)

## Build
INCLUDE_DIRECTORIES(
    ${FLTK_INCLUDE_DIR}
    ${RAKNET_INCLUDE_DIR}
)

ADD_DEFINITIONS(-DREPORT_DOMAIN="scary-squid.de")

SET(CMAKE_INSTALL_RPATH "@loader_path/.")
ADD_EXECUTABLE(CrashHandler ${SOURCES} ${HEADERS})

TARGET_LINK_LIBRARIES(CrashHandler
  ${FLTK_LIBRARIES}
  ${MCORE_LIBRARIES}
  ${RAKNET_LIBRARIES}
)

INSTALL(TARGETS CrashHandler DESTINATION ${MARATIS_INSTALL_DIR})

