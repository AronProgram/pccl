
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_executable(HelloApi ${GLOBAL_SOURCES})


include_directories("./"  
					"./api"
					"${PCCL_FRAMEWORK_RPC}"					
					)


target_link_libraries(HelloApi 
					  pccl_logicrpc
					 )



