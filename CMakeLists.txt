#################################################### 
## project 
## 
####################################################
cmake_minimum_required (VERSION 3.0)
project (PCCL)


#################################################### 
## project 
## 
####################################################



set(THIRDPARTY_DIR "${CMAKE_SOURCE_DIR}/thirdparty")




####################################################
## third library
## 
####################################################

#find_package(Protobuf "3.5.1")
#find_package(Openssl)

#FIND_PACKAGE(CURL)
#IF(CURL_FOUND)
#    INCLUDE_DIRECTORIES(${CURL_INCLUDE_DIR})
#    #TARGET_LINK_LIBRARIES(curltest ${CURL_LIBRARY})
#ELSE(CURL_FOUND)
#    MESSAGE(FATAL_ERROR "CURL library not found")
#ENDIF(CURL_FOUND)





####################################################
## binary
## 
####################################################


####################################################
## add dir
## 
####################################################

add_subdirectory(src)

#add_subdirectory(thirdparty)




