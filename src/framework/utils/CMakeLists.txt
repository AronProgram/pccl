
file(GLOB_RECURSE  GLOBAL_SOURCES "*.cpp" "*.h" )

add_library(pccl_utils STATIC ${GLOBAL_SOURCES})

include_directories( "./" "${CMAKE_SOURCE_DIR}/third/random/include")



