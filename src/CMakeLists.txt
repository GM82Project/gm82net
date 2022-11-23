set(SRCS gm.cpp
	     gm_buffer.cpp
		 gm_hash.cpp
		 gm_httprequest.cpp
		 gm_listeningsocket.cpp
		 gm_socket.cpp
		 gm_udpsocket.cpp
		 gm_pipe.cpp
		 
		 Buffer.cpp
		 Hash.cpp
		 HttpRequest.cpp
		 Socket.cpp
		 StringConversion.cpp
)

add_library(gm82net SHARED ${SRCS})

if (CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(TARGET_ARCH "x86")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(TARGET_ARCH "x64")
endif()

target_link_libraries(gm82net Ws2_32 "${PROJECT_SOURCE_DIR}/lib/${TARGET_ARCH}/zlibstatic.lib")

option(INSTALL_GEX "Install the generated .gex" OFF)
option(NO_GEX "Omit building a .gex" OFF)

if (NOT NO_GEX)
	if (INSTALL_GEX)
		add_custom_command(
			TARGET gm82net
			POST_BUILD
			COMMAND py build_gex.py gm82net.gej
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
			COMMENT "Building .gex"
		)
	else()
		add_custom_command(
			TARGET gm82net
			POST_BUILD
			COMMAND py build_gex.py gm82net.gej --noinstall
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
			COMMENT "Building .gex"
		)
	endif()
endif()
