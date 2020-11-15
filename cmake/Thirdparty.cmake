#################################################### 
## option 
## 
####################################################

set(THIRDPARTY_PATH "${PROJECT_SOURCE_DIR}/thirdparty")

option(TARS_CPP         "option for TarsCpp"   ON)
option(JSON_CPP         "option for jsoncpp"   ON)
option(RANDOM_CPP       "option for random"    ON)
option(FMT_CPP          "option for fmt"       ON)
option(PROTOBUFF_CPP    "option for protobuff" ON)
option(JWT_CPP          "option for jwt"       ON)
option(OPENSSL_CPP      "option for openssl"   ON)

#################################################### 
## definitions 
## 
####################################################

#if (TARS_CPP)
#    add_definitions(-DTARS_CPP=1)
#endif ()


#################################################### 
## zlib/curl
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



IF(UNIX)
	
    FIND_PACKAGE(CURL)
    IF(CURL_FOUND)
		 include_directories(${CURL_INCLUDE_DIRS})
    ENDIF()
    
ENDIF(UNIX)


IF(UNIX)
	
    FIND_PACKAGE(CURL)
    IF(CURL_FOUND)
		 include_directories(${CURL_INCLUDE_DIRS})
    ENDIF()

	FIND_PACKAGE(Protobuf REQUIRED)
	IF(PROTOBUF_FOUND)
	    message(STATUS "protobuf library found")
	    INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIRS})
		INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
	ELSE()
	    message(FATAL_ERROR "protobuf library is needed but cant be found")
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
## RANDOM_CPP 
## 
####################################################

if (FMT_CPP)

    set(FMT_DIR_INC "/usr/local/include")
    include_directories(${FMT_DIR_INC})   

    set(LIB_FMT "fmt")

    ExternalProject_Add(ADD_${LIB_FMT}                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
            SOURCE_DIR ${THIRDPARTY_PATH}/fmt
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make
            INSTALL_COMMAND make  install
            )

endif (FMT_CPP)

#################################################### 
## PROTOBUFF_CPP 
## 
####################################################

if (PROTOBUFF_CPP)

	set(LIB_PROTOBUFF "libprotobuf.a")
    set(PROTOBUFF_DIR_INC "/usr/local/include")
    set(PROTOBUFF_LIB_DIR "/usr/local/lib64")
    
    include_directories(${PROTOBUFF_DIR_INC})   
	link_directories(${PROTOBUFF_LIB_DIR})
    

    ExternalProject_Add(ADD_${LIB_PROTOBUFF}                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . -Dprotobuf_BUILD_TESTS=OFF
            SOURCE_DIR ${THIRDPARTY_PATH}/protobuf/cmake
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make
            INSTALL_COMMAND make  install
            )

endif (PROTOBUFF_CPP)



#################################################### 
## JWT_CPP 
## 
####################################################

if (JWT_CPP)

	set(LIB_JWT "libjwt.a")
    set(JWT_DIR_INC "/usr/local/include")
    set(JWT_LIB_DIR "/usr/local/jwt-cpp")
    
    include_directories(${JWT_DIR_INC})   
	#link_directories(${JWT_LIB_DIR})
    

    ExternalProject_Add(ADD_${LIB_JWT}                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . -DBUILD_TESTS=0
            SOURCE_DIR ${THIRDPARTY_PATH}/jwt
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make
            INSTALL_COMMAND make  install
            )

endif (JWT_CPP)

#################################################### 
## OPENSSL_CPP 
## 
####################################################
if (OPENSSL_CPP)

	set(LIB_OPENSSL "libopenssl.a")
    set(OPENSSL_DIR_INC "/usr/local/include")
    set(OPENSSL_LIB_DIR "/usr/local/openssl")
    
    include_directories(${OPENSSL_DIR_INC})   
	link_directories(${OPENSSL_LIB_DIR})
    

    ExternalProject_Add(ADD_${LIB_OPENSSL}                
            CONFIGURE_COMMAND ./config
            SOURCE_DIR ${THIRDPARTY_PATH}/openssl
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make
            INSTALL_COMMAND make  install
            )

endif (OPENSSL_CPP)


#################################################### 
## message 
## 
####################################################
message("----------------------------------------------------")
message("TARS_CPP:                  ${TARS_CPP}")
message("JSON_CPP:                  ${JSON_CPP}")
message("RANDOM_CPP:                ${RANDOM_CPP}")
message("FMT_CPP:                   ${FMT_CPP}")
message("PROTOBUFF_CPP:             ${PROTOBUFF_CPP}")
message("JWT_CPP:                   ${JWT_CPP}")
message("OPENSSL_CPP:               ${OPENSSL_CPP}")
message("----------------------------------------------------")


