
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_library(pccl_fastapi STATIC ${GLOBAL_SOURCES} )

include_directories("." 
					"../common"
					)


target_link_libraries(	pccl_fastapi 
						${LIB_JSONCPP} 						
						${LIB_FMT}
						${LIB_TARS_CPP} 
						pthread
						)




