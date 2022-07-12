set(SRCS gm.cpp
	     gm_buffer.cpp
		 gm_hash.cpp
		 gm_httprequest.cpp
		 gm_listeningsocket.cpp
		 gm_socket.cpp
		 gm_udpsocket.cpp
		 
		 Buffer.cpp
		 Hash.cpp
		 HttpRequest.cpp
		 Socket.cpp
		 StringConversion.cpp
)

add_library(gm82net SHARED ${SRCS})

target_link_libraries(gm82net Ws2_32 "${PROJECT_SOURCE_DIR}/lib/zlibstatic.lib")

option(INSTALL_GEX "Install the generated .gex" OFF)

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
