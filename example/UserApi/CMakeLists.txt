
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_executable(UserApi ${GLOBAL_SOURCES})


include_directories("./"  
					"./api"
					"${PCCL_FRAMEWORK_API}"					
					)


target_link_libraries(UserApi 
					pccl_fastapi
					)



