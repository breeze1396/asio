#include "asio.hpp"

#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/read_until.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>
#include <cstdio>
#include <iostream>
#include <memory>
#include <thread>

using asio::ip::tcp;
using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::use_awaitable;
namespace this_coro = asio::this_coro;

class client {
public:
    client(asio::io_context& io_context, const tcp::endpoint& endpoint)
        : _io_context(io_context)
        ,_socket(io_context)
    {
        co_spawn(io_context, connect(endpoint), detached);
    }

    awaitable<void> connect(const tcp::endpoint& endpoint) {
        co_await _socket.async_connect(endpoint, use_awaitable);
        // Start receiver coroutine to print server broadcasts (including welcome message)
        co_spawn(_io_context, receive(), detached);

        std::thread([this]{
            std::string msg;
            while (std::getline(std::cin, msg)) {
                msg += "\n";
                std::string to_send = msg; // copy for move into coroutine
                co_spawn(_io_context, this->send(std::move(to_send)), detached);
            }
        }).detach();
        co_return;
    }

    awaitable<void> send(const std::string& msg) {
        co_await asio::async_write(_socket, asio::buffer(msg), use_awaitable);
    }

    awaitable<void> receive() {
        std::string buffer;
        try {
            for (;;) {
                std::size_t n = co_await asio::async_read_until(_socket, asio::dynamic_buffer(buffer), '\n', use_awaitable);
                std::string line(buffer.substr(0, n));
                buffer.erase(0, n);
                std::cout << line; // line already contains trailing \n
            }
        } catch (std::exception& e) {
            // Socket closed or other error; exit quietly
            co_return;
        }
    }
    
private:
    asio::io_context& _io_context;
    asio::ip::tcp::socket _socket;
};

int main(){
    try {
        asio::io_context io_context;

        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "12345");
        client c(io_context, *endpoints.begin());
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}