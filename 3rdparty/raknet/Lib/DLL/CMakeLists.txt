cmake_minimum_required(VERSION 2.6)
project(RakNetDLL)

FILE(GLOB ALL_HEADER_SRCS ${RakNet_SOURCE_DIR}/Source/*.h)
FILE(GLOB ALL_CPP_SRCS ${RakNet_SOURCE_DIR}/Source/*.cpp)


include_directories( ${RAKNET_INTERNAL_INCLUDE_DIRS} ) 

add_library(RakNetDLL SHARED ${ALL_CPP_SRCS} ${ALL_HEADER_SRCS} readme.txt)
	
#IF(WIN32 AND NOT UNIX)
#	SET( CMAKE_CXX_FLAGS "/D WIN32 /D _RAKNET_DLL /D _CRT_NONSTDC_NO_DEPRECATE /D _CRT_SECURE_NO_DEPRECATE /GS- /GR- ")
#ENDIF(WIN32 AND NOT UNIX)

IF(WIN32 AND NOT UNIX)
	target_link_libraries (RakNetDLL ${RAKNET_LIBRARY_LIBS})
ELSE(WIN32 AND NOT UNIX)
	target_link_libraries (RakNetDLL ${RAKNET_LIBRARY_LIBS})
        #INSTALL(TARGETS RakNetDLL DESTINATION ${RakNet_SOURCE_DIR}/Lib/DLL)
ENDIF(WIN32 AND NOT UNIX)
