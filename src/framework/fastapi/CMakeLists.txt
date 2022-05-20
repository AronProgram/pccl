
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_library(pccl_fastapi STATIC ${GLOBAL_SOURCES} )

include_directories("." 
					"../common"
					)


target_link_libraries(	pccl_fastapi 
						${JSONCPP_LIBRARY} 						
						${FMT_LIBRARY}
						${TARSCPP_LIBRARY} 
						pthread
						)




