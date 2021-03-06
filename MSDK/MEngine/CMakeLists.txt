## Find source and headers
FILE(GLOB HEADERS Includes/*.h)
FILE(GLOB SOURCES Sources/*.c*)

IF(CMAKE_HAS_SORT)
  LIST(SORT HEADERS)
  LIST(SORT SOURCES)
ENDIF(CMAKE_HAS_SORT)

## Build
INCLUDE_DIRECTORIES(
  ${MCORE_INCLUDE_DIR}
  ${MENGINE_INCLUDE_DIR}
  ${SDL_INCLUDE_DIR}
)

SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}")

ADD_DEFINITIONS(-DMENGINE_DLL)

IF(NOT ANDROID AND NOT EMSCRIPTEN)
	ADD_LIBRARY(MEngine SHARED ${SOURCES} ${HEADERS})
ELSE()
	ADD_LIBRARY(MEngine STATIC ${SOURCES} ${HEADERS})
ENDIF()

TARGET_LINK_LIBRARIES(MEngine ${MCORE_LIBRARIES})

## Install for Editor
INSTALL(TARGETS MEngine DESTINATION ${MARATIS_INSTALL_DIR})

## Install for SDK
INSTALL(TARGETS MEngine DESTINATION ${MARATIS_INSTALL_DIR}/SDK/lib)
INSTALL(FILES ${HEADERS} DESTINATION ${MARATIS_INSTALL_DIR}/SDK/include/MEngine)
