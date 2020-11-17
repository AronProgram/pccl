


####################################################
## function 
## pb文件生成cpp文件
## 
####################################################
function (build_proto_files arg)
    #message(STATUS "ARGC: ${ARGC}")
    #message(STATUS "ARGV: ${ARGV}")

    list(LENGTH ARGV  argv_len)
    #message(STATUS "length of ARGV: ${argv_len}")


    set(i 0)
    while( i LESS ${argv_len})
		list(GET ARGV ${i} FIL)
		message(STATUS "argv${i}: ${FIL}")

		GET_FILENAME_COMPONENT(FIL_PATH ${FIL} PATH)
		EXECUTE_PROCESS (
		    COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} ${PROTO_FLAGS} --cpp_out=${FIL_PATH} ${FIL} --proto_path=${FIL_PATH}
		)

		#message("FIL: ${FIL},PATH: ${FIL_PATH} " )
		
        math(EXPR i "${i} + 1")
         
    endwhile()


endfunction ()


