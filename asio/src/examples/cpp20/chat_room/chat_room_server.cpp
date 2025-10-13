
/*
基于 C++23 ，使用 asio 协程实现的 chat_room_server.cpp 示例代码。
*/

#include "asio.hpp"

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>
#include <cstdio>
#include <iostream>
#include <memory>

using asio::ip::tcp;
using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::use_awaitable;
namespace this_coro = asio::this_coro;

class server;
class session;



class session : public std::enable_shared_from_this<session> {
public:
    session(asio::ip::tcp::socket socket, std::shared_ptr<server> server);

    void start();

    awaitable<void> deliver(const std::string& msg) {
        try {
            co_await asio::async_write(_socket, asio::buffer(msg), use_awaitable);
        } catch (std::exception& e) {
            std::cout << "Error sending message: " << e.what() << std::endl;
        }
    }

private:
    awaitable<void> do_read();

    asio::ip::tcp::socket _socket;
    std::shared_ptr<server> _server;

    enum { max_length = 1024 };
    char _data[max_length];
};



class server : public std::enable_shared_from_this<server> {
public:
    server(asio::io_context& io_context, short port)
        : _acceptor(io_context, tcp::endpoint(tcp::v4(), port))
        , _io_context(io_context)
    {
    }
    
    void start() {
        co_spawn(_io_context, do_accept(), detached);
    }

    void broadcast(const std::string& message, std::shared_ptr<session> who_send = nullptr) {
        for (auto& session : _sessions) {
            if(who_send == session){   // 不发送给自己 
                continue; 
            } 
            co_spawn(_io_context, session->deliver(message), detached);
        }
    }

    asio::io_context& get_context() {
        return _io_context;
    }

private:
    awaitable<void> do_accept() {
        for(;;) {
            tcp::socket socket = co_await _acceptor.async_accept(use_awaitable);
            auto ss = std::make_shared<session>(std::move(socket), shared_from_this());
            _sessions.push_back(ss);
            ss->start();
        }
    }

    tcp::acceptor _acceptor;
    asio::io_context& _io_context;

    std::vector<std::shared_ptr<session>> _sessions;
};

inline session::session(asio::ip::tcp::socket socket, std::shared_ptr<server> server)
    : _socket(std::move(socket))
    , _server(server) {
    _socket.set_option(asio::ip::tcp::no_delay(true));
}

inline void session::start() {
    co_spawn(_server->get_context(), deliver("Welcome to the chat room!\n"), detached);
    co_spawn(_server->get_context(), do_read(), detached);
}

inline awaitable<void> session::do_read() {
    try {
        for(;;) {
            std::size_t n = co_await _socket.async_read_some(asio::buffer(_data), use_awaitable);
            std::cout << "Received: " << std::string(_data, n) << std::endl;
            _server->broadcast(std::string(_data, n), shared_from_this());
        }
    } catch (std::exception& e) {
        // 连接断开或其他错误，安静地退出
        co_return;
    }
}




int main() {
    try {
        asio::io_context io_context;

        asio::signal_set signals(io_context, SIGINT, SIGTERM);
        signals.async_wait([&](auto, auto){ io_context.stop(); });

        auto srv = std::make_shared<server>(io_context, 12345);
        srv->start();

        std::cout << "Chat room server started on port 12345..." << std::endl;
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
