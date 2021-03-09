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
        MESSAGE(FATAL_ERROR ${ERRORMSG})
    ELSE(ZLIB_FOUND)
		include_directories(${ZLIB_INCLUDE_DIRS})
    ENDIF()
    

    FIND_PACKAGE(CURL)
    IF(NOT CURL_FOUND)    
		SET(ERRORMSG "curl library not found. Please install appropriate package, remove CMakeCache.txt and rerun cmake.")        
        MESSAGE(FATAL_ERROR ${ERRORMSG})
	ELSE(CURL_FOUND)
		include_directories(${CURL_INCLUDE_DIRS})
    ENDIF()

	FIND_PACKAGE(Protobuf REQUIRED)
	IF(NOT PROTOBUF_FOUND)
	    SET(ERRORMSG "protobuf library not found. Please install appropriate package, remove CMakeCache.txt and rerun cmake.")        
        MESSAGE(FATAL_ERROR ${ERRORMSG})
	ELSE(PROTOBUF_FOUND)	
	    INCLUDE_DIRECTORIES(${PROTOBUF_INCLUDE_DIRS})
		INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
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
    set(LIB_TARS_CPP "libtarsservant.a" "libtarsparse.a" "libtarsutil.a")
    
    include_directories(${TARS_CPP_DIR_INC})
    link_directories(${TARS_CPP_LIB_DIR})


	if (NOT EXISTS "${THIRDPARTY_PATH}/TarsCpp/lib/libtarsservant.a" )
	
	    ExternalProject_Add(ADD_tarscpp                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
            SOURCE_DIR ${THIRDPARTY_PATH}/TarsCpp
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make 
            INSTALL_COMMAND make  install
            )  
            
	endif()



endif (TARS_CPP)

#################################################### 
## JSON_CPP 
## 
####################################################

if (JSON_CPP)

    set(JSONCPP_DIR_INC "/usr/local/include/json")
    
    include_directories(${JSONCPP_DIR_INC})
    link_directories(${JSONCPP_LIB_DIR})

    set(LIB_JSONCPP "${THIRDPARTY_PATH}/jsoncpp/lib/libjsoncpp_static.a")

    if (NOT EXISTS "${THIRDPARTY_PATH}/jsoncpp/lib/libjsoncpp_static.a" )
	
 		ExternalProject_Add(ADD_jsoncpp                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
            SOURCE_DIR ${THIRDPARTY_PATH}/jsoncpp
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make
            INSTALL_COMMAND make  install
            ) 
            
	endif()

   
endif (JSON_CPP)


#################################################### 
## RANDOM_CPP 
## 
####################################################

if (RANDOM_CPP)

    set(RANDOM_DIR_INC "/usr/local/include")
    include_directories(${RANDOM_DIR_INC})   

    ExternalProject_Add(ADD_random                
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

    set(LIB_FMT "${THIRDPARTY_PATH}/fmt/libfmt.a")

    if (NOT EXISTS "${LIB_FMT}" )

	    ExternalProject_Add(ADD_fmt               
	            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
	            SOURCE_DIR ${THIRDPARTY_PATH}/fmt
	            BUILD_IN_SOURCE 1
	            BUILD_COMMAND make
	            INSTALL_COMMAND make  install
	            )

     endif()

endif (FMT_CPP)




#################################################### 
## message 
## 
####################################################
message("----------------------------------------------------")
message("TARS_CPP:                  ${TARS_CPP}  ${LIB_TARS_CPP}")
message("JSON_CPP:                  ${JSON_CPP}  ${LIB_JSONCPP}")
message("RANDOM_CPP:                ${RANDOM_CPP}")
message("FMT_CPP:                   ${FMT_CPP} ${LIB_FMT} ")
message("----------------------------------------------------")


