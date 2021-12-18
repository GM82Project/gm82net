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

add_definitions(-DZLIB_WINAPI)
add_library(gm82net SHARED ${SRCS})
target_link_libraries(gm82net Ws2_32 "${PROJECT_SOURCE_DIR}/lib/zlibwapi.lib")