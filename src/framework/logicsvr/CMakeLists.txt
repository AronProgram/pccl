



execute_process(WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" COMMAND  protoc  Packet.proto --cpp_out=./)
message(STATUS "protoc protobuf file: ${CMAKE_CURRENT_SOURCE_DIR} ...")

### compile
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.cc" "*.h" )

add_library(pccl_logicsvr STATIC ${GLOBAL_SOURCES})

include_directories("./include" "${CMAKE_SOURCE_DIR}/pccl"  "${CMAKE_SOURCE_DIR}/third/jsoncpp-1.9.2/include/json" "${CMAKE_SOURCE_DIR}/third/random/include" "${FMT_DIR}")


target_link_libraries(pccl_logicsvr pccl_utils ${FMT_LIBRARY} ${jsoncpp_LIBRARIES}  ${Protobuf_LIBRARIES} ${TARS_LIBRARIES}  )




