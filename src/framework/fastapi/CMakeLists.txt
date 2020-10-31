
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_library(pccl_fastapi STATIC ${GLOBAL_SOURCES} )

include_directories("." 
					"../common"
					)


target_link_libraries(	pccl_fastapi 
						#${jsoncpp_LIBRARIES} 
						#${TARS_LIBRARIES} 
						pthread  
						)




