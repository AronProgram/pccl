
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_executable(UserApi ${GLOBAL_SOURCES})


include_directories("./"  
					"${CMAKE_SOURCE_DIR}/pccl" 
					"${RapidJSON_INCLUDE_DIR}" 
					"${FASTCGI_DIR}"
					)


target_link_libraries(UserApi 
					pccl_utils 
					pccl_fastcgi 
					${TARS_LIBRARIES} 
					pthread  
					)



