############################################################################################################################################################  
## option 
## 
############################################################################################################################################################  

set(THIRDPARTY_PATH "${PROJECT_SOURCE_DIR}/thirdparty")

option(TARSCPP          "option for TarsCpp"   ON)
option(JSONCPP          "option for jsoncpp"   ON)
option(RANDOM           "option for random"    ON)
option(FMT              "option for fmt"       ON)


############################################################################################################################################################   
## definitions 
## 
############################################################################################################################################################  

#if (TARS_CPP)
#    add_definitions(-DTARS_CPP=1)
#endif ()


############################################################################################################################################################   
## zlib/curl
## apt install libcurl4-openssl-dev
## apt install zip
############################################################################################################################################################  

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




############################################################################################################################################################   
## TARSCPP 
## 
############################################################################################################################################################  

add_custom_target(thirdparty)
include(ExternalProject)

if (TARSCPP)

    set(TARSCPP_INCLUDE_DIRS "/usr/local/tars/cpp/include")
    set(TARSCPP_LIBRARY_DIRS "/usr/local/tars/cpp/lib") 
    set(TARSCPP_LIBRARY      "/usr/local/tars/cpp/lib/libtarsservant.a" "/usr/local/tars/cpp/lib/libtarsparse.a" "/usr/local/tars/cpp/lib/libtarsutil.a")
    
    include_directories(${TARSCPP_INCLUDE_DIRS})
    link_directories(${TARSCPP_LIBRARY_DIRS})


	if (NOT EXISTS "${THIRDPARTY_PATH}/TarsCpp/lib/libtarsservant.a" )
	
	    ExternalProject_Add(ADD_tarscpp                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
            SOURCE_DIR ${THIRDPARTY_PATH}/TarsCpp
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make 
            INSTALL_COMMAND make  install
            )  
            
	endif()


endif (TARSCPP)

############################################################################################################################################################   
## JSONCPP 
## 
############################################################################################################################################################  

if (JSONCPP)
	
    set(JSONCPP_INCLUDE_DIRS "/usr/local/include/json")
    set(JSONCPP_LIBRARY      "/usr/local/lib/libjsoncpp.a" )
    
    include_directories(${JSONCPP_INCLUDE_DIRS})
	

    if (NOT EXISTS "${THIRDPARTY_PATH}/jsoncpp-Sandbox/jsoncpp/jsoncpp-build/lib/libjsoncpp.a" )
		
 		ExternalProject_Add(ADD_jsoncpp                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} ..
            SOURCE_DIR ${THIRDPARTY_PATH}/jsoncpp-Sandbox/jsoncpp/jsoncpp-build
            BUILD_IN_SOURCE 1
            BUILD_COMMAND   make
            INSTALL_COMMAND make  install
            ) 
            
	endif()

   
endif (JSONCPP)


############################################################################################################################################################   
## RANDOM 
## 
############################################################################################################################################################  

if (RANDOM)

    set(RANDOM_INCLUDE_DIRS "/usr/local/include")
    set(RANDOM_LIBRARY      "/usr/local/lib/librandom.a" )
    
    include_directories(${RANDOM_INCLUDE_DIRS})   


    ExternalProject_Add(ADD_random                
            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
            SOURCE_DIR ${THIRDPARTY_PATH}/random
            BUILD_IN_SOURCE 1
            BUILD_COMMAND make
            INSTALL_COMMAND make  install
            )

endif (RANDOM)



############################################################################################################################################################   
## FMT 
## 
############################################################################################################################################################  

if (FMT)

    set(FMT_INCLUDE_DIRS "/usr/local/include")
    set(FMT_LIBRARY      "/usr/local/lib/libfmt.a" )
    
    include_directories(${FMT_INCLUDE_DIRS})   

    if (NOT EXISTS "${THIRDPARTY_PATH}/fmt/libfmt.a" )

	    ExternalProject_Add(ADD_fmt               
	            CONFIGURE_COMMAND ${CMAKE_COMMAND} . 
	            SOURCE_DIR ${THIRDPARTY_PATH}/fmt
	            BUILD_IN_SOURCE 1
	            BUILD_COMMAND make
	            INSTALL_COMMAND make  install
	            )

     endif()

endif (FMT)




############################################################################################################################################################   
## message 
## 
############################################################################################################################################################  
message("----------------------------------------------------")
message("ZLIB:                        zlib | Find(${ZLIB_FOUND}) ")
message("ZLIB_INCLUDE_DIRS:           ${ZLIB_INCLUDE_DIRS} ")
message("ZLIB_LIBRARY:                ${ZLIB_LIBRARY} ")
message("----------------------------------------------------")
message("CURL:                        curl | Find(${CURL_FOUND}) ")
message("CURL_INCLUDE_DIRS:           ${CURL_INCLUDE_DIRS} ")
message("CURL_LIBRARY:                ${CURL_LIBRARY} ")
message("----------------------------------------------------")
message("PROTOBUF:                     protobuff | Find(${PROTOBUF_FOUND}) ")
message("PROTOBUF_INCLUDE_DIRS:        ${PROTOBUF_INCLUDE_DIRS}")
message("PROTOBUF_LIBRARY:             ${PROTOBUF_LIBRARY}")
message("----------------------------------------------------")
message("TARSCPP:                     TarsCpp | ${TARSCPP} ")
message("TARSCPP_INCLUDE_DIRS:        ${TARSCPP_INCLUDE_DIRS}")
message("TARSCPP_LIBRARY:             ${TARSCPP_LIBRARY}")
message("----------------------------------------------------")
message("JSONCPP:                     jsoncpp | ${JSONCPP} ")
message("JSONCPP_INCLUDE_DIRS:        ${JSONCPP_INCLUDE_DIRS}")
message("JSONCPP_LIBRARY:             ${JSONCPP_LIBRARY}")
message("----------------------------------------------------")
message("RANDOM:                      random | ${RANDOM} ")
message("RANDOM_INCLUDE_DIRS:        ${RANDOM_INCLUDE_DIRS}")
message("RANDOM_LIBRARY:             ${RANDOM_LIBRARY}")
message("----------------------------------------------------")
message("FMT:                        fmt | ${FMT} ")
message("FMT_INCLUDE_DIRS:           ${FMT_INCLUDE_DIRS}")
message("FMT_LIBRARY:                ${FMT_LIBRARY}")
message("----------------------------------------------------")



