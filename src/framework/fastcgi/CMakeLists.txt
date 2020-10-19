
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_library(pccl_fastcgi STATIC ${GLOBAL_SOURCES})

include_directories("./include" "${CMAKE_SOURCE_DIR}/pccl" 
					"${THIRDPARTY_DIR}/jsoncpp-1.9.2/include/json" 
					"${THIRDPARTY_DIR}/third/random/include"
					)


target_link_libraries(	pccl_fastcgi pccl_utils 
						${jsoncpp_LIBRARIES} 
						${TARS_LIBRARIES} 
						pthread  
						)




