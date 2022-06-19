link_libraries(ST)

add_executable(daytime-tcp-client daytime_tcp_client.cpp)
# target_link_libraries(daytime-tcp-client PRIVATE ST)
add_executable(daytime-tcp-server daytime_tcp_server.cpp)

add_executable(tcp-echo-server tcp_echo_server.cpp)
add_executable(tcp-echo-client tcp_echo_client.cpp)