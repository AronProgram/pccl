
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(pccl_logicrpc STATIC ${GLOBAL_SOURCES} )

include_directories("." 					
					)


target_link_libraries(	pccl_logicrpc 
						${JSONCPP_LIBRARY} 						
						${FMT_LIBRARY}
						${TARSCPP_LIBRARY} 
						pthread
						)




