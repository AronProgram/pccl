#################################################### 
## option 
## 
####################################################

set(THIRDPARTY_PATH "${PROJECT_SOURCE_DIR}/thirdparty")

option(TARS_CPP   "option for TarsCpp" ON)
option(JSON_CPP   "option for jsoncpp" ON)
option(RANDOM_CPP "option for random" ON)

#################################################### 
## definitions 
## 
####################################################

#if (TARS_CPP)
#    add_definitions(-DTARS_CPP=1)
#endif ()


#################################################### 
## zlib 
## 
####################################################

IF(UNIX)
    FIND_PACKAGE(ZLIB)
    IF(NOT ZLIB_FOUND)
        SET(ERRORMSG "zlib library not found. Please install appropriate package, remove CMakeCache.txt and rerun cmake.")
        IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
            SET(ERRORMSG ${ERRORMSG} "On Debian/Ubuntu, package name is zlib1g-dev(apt-get install  zlib1g-dev), on Redhat/Centos and derivates it is zlib-devel (yum install zlib-devel).")
        ENDIF()
        MESSAGE(FATAL_ERROR ${ERRORMSG})
    ENDIF()
ENDIF(UNIX)


#################################################### 
## TARS_CPP 
## 
####################################################

add_custom_target(thirdparty)
include(ExternalProject)

if (TARS_CPP)

    set(TARS_CPP_DIR_INC "/usr/local/tars/cpp/include")
    set(TARS_CPP_LIB_DIR "/usr/local/tars/cpp/lib")
    set(TARS_CPP_LIB "libtarsservant.a libtarsparse.a libtarsutil.a")
    include_directories(${TARS_CPP_DIR_INC})
    link_directories(${TARS_CPP_LIB_DIR})

    set(LIB_TARSCPP "tarscpp")

    ExternalProject_Add(ADD_${LIB_TARSCPP}                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
            SOURCE_DIR ${THIRDPARTY_PATH}/TarsCpp
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make 
            INSTALL_COMMAND make  install
            )

endif (TARS_CPP)

#################################################### 
## JSON_CPP 
## 
####################################################

if (JSON_CPP)

    set(JSONCPP_DIR_INC "/usr/local/include/json")
    set(JSONCPP_LIB_DIR "/usr/local/lib64")
    set(JSONCPP_LIB "libjsoncpp_static.a")
    include_directories(${JSONCPP_DIR_INC})
    link_directories(${JSONCPP_LIB_DIR})

    set(LIB_JSONCPP "jsoncpp")

    ExternalProject_Add(ADD_${LIB_JSONCPP}                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
            SOURCE_DIR ${THIRDPARTY_PATH}/jsoncpp
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make
            INSTALL_COMMAND make  install
            )

endif (JSON_CPP)


#################################################### 
## RANDOM_CPP 
## 
####################################################

if (RANDOM_CPP)

    set(RANDOM_DIR_INC "/usr/local/include")
    include_directories(${RANDOM_DIR_INC})   

    set(LIB_RANDOM "random")

    ExternalProject_Add(ADD_${LIB_RANDOM}                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
            SOURCE_DIR ${THIRDPARTY_PATH}/random
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make
            INSTALL_COMMAND make  install
            )

endif (RANDOM_CPP)

#################################################### 
## message 
## 
####################################################
message("----------------------------------------------------")
message("TARS_CPP:                  ${TARS_CPP}")
message("JSON_CPP:                  ${JSON_CPP}")
message("RANDOM_CPP:                ${RANDOM_CPP}")
message("----------------------------------------------------")


