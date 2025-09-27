
add_executable(chat_client chat_client.cpp)
add_executable(chat_server chat_server.cpp)


link_example(chat_client)
link_example(chat_server)