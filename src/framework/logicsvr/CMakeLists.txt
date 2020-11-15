




file(GLOB_RECURSE  GLOB_PROTO_SRCS   "*.proto" )

build_proto_files( ${GLOB_PROTO_SRCS} )

### compile
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.cc" "*.h" )

add_library(pccl_logicsvr STATIC ${GLOBAL_SOURCES} ${PROTO_SRCS} )

include_directories("." 
					"../common"
					"./pb"
					)


target_link_libraries(	pccl_logicsvr 
						#${TARS_LIBRARIES} 
						${PROTOBUF_LIBRARIES}
						pthread  
						)



