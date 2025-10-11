/*
本代码是额外增加测试的代码，用于测试 tcp::no_delay 选项所带来的影响。

TCP_NODELAY 的作用原理：
1. **Nagle算法**：默认情况下，TCP使用Nagle算法来减少小包数量，提高网络效率
   - Nagle算法会等待直到有足够数据(通常是MSS大小)或收到ACK才发送
   - 这会增加小包的延迟，但减少网络包数量

2. **TCP_NODELAY效果**：
   - 启用(true): 禁用Nagle算法，立即发送数据，降低延迟
   - 禁用(false): 启用Nagle算法，可能合并小包，但增加延迟

3. **适用场景**：
   - 启用no_delay: 实时应用(游戏、VoIP、交互式应用)，对延迟敏感
   - 禁用no_delay: 批量数据传输，对吞吐量要求高，延迟不敏感

4. **测试说明**：
   - 本测试在本地回环(127.0.0.1)进行，延迟影响较小
   - 在实际网络环境中，特别是高延迟网络，效果会更明显
   - 小包(10-200字节)最能体现no_delay的影响
*/


#include <iostream>
#include <memory>
#include <queue>
#include <thread>
#include <chrono>
#include <vector>

#include "asio.hpp"
#include "asio/steady_timer.hpp"

using asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
public:
  session(asio::ip::tcp::socket socket, bool enable_no_delay = true)
    : socket_(std::move(socket)), enable_no_delay_(enable_no_delay)
  {
    socket_.set_option(asio::ip::tcp::no_delay(enable_no_delay_));
    std::cout << "Session created with no_delay=" << (enable_no_delay_ ? "true" : "false") << "\n";
  }
    void start()
    {
        do_read();
    }
    ~session() {
        std::cout << "Session ended. Total messages received: " << count_ << "\n";
    }
private:
    void do_read()
    {
        auto self(shared_from_this());
        socket_.async_read_some(asio::buffer(data_, max_length),
            [this, self](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    // 只有收到完整消息（以'\n'结尾）才计数
                    if(length > 0 && data_[length-1] == '\n'){
                        count_++;
                        if(count_ % 10000 == 0){
                            // std::cout << "Server received " << count_ << " messages\n";
                        }
                    }
                    do_read();
                }
            });
    }
    
    asio::ip::tcp::socket socket_;
    enum { max_length = 102400 };
    char data_[max_length];

    int count_{0};
    bool enable_no_delay_;
};


class server
{
public:
    server(asio::io_context& io_context, const tcp::endpoint& endpoint, bool enable_no_delay = true)
        : acceptor_(io_context, endpoint), enable_no_delay_(enable_no_delay)
    {
        // 设置SO_REUSEADDR选项，允许端口重用
        acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
        do_accept();
    }
private:
    void do_accept()
    {
        acceptor_.async_accept(
            [this](std::error_code ec, tcp::socket socket)
            {
            if (!ec)
            {
                std::make_shared<session>(std::move(socket), enable_no_delay_)->start();
                }
                do_accept();
            });
    }
    tcp::acceptor acceptor_;
    bool enable_no_delay_;
};

class client
{
public:
    client(asio::io_context& io_context, const tcp::endpoint& endpoint, int test_size, bool enable_no_delay = true)
        : socket_(io_context), test_data_size_(test_size), message_count_(0)
    {
        
        socket_.async_connect(endpoint,
            [this, enable_no_delay](std::error_code ec)
            {
            if (!ec)
            {
                std::cout << "Testing with message size: " << test_data_size_ << " bytes\n";
                start_time_ = std::chrono::steady_clock::now();
               
                socket_.set_option(asio::ip::tcp::no_delay(enable_no_delay)); // 客户端始终启用no_delay以减少发送延迟
                do_write();
            }
            });
    }
    
    int get_message_count() const { return message_count_; }
    
private:
    void do_write() 
    {
        std::string msg(test_data_size_, 'A');
        msg.back() = '\n';  // 标记消息结束
        
        asio::async_write(socket_, asio::buffer(msg),
            [this](std::error_code ec, std::size_t /*length*/)
            {
            if (!ec)
            {
                message_count_++;
                
                if(message_count_ % 10000 == 0) {
                    auto now = std::chrono::steady_clock::now();
                    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time_).count();
                    if(elapsed > 0) {
                        double throughput = (double)message_count_ * test_data_size_ * 1000.0 / elapsed / 1024 / 1024; // MB/s
                        double msg_rate = (double)message_count_ * 1000.0 / elapsed; // messages/s
                        std::cout << "Progress: " << message_count_ << " msgs, " 
                                  << throughput << " MB/s, " 
                                  << msg_rate << " msgs/s\n";
                    }
                }
                
                do_write();
                // 对于小包，几乎不等待以体现Nagle算法的影响
                if(test_data_size_ <= 200) {
                    // 小包快速发送，让Nagle算法有机会合并
                    std::this_thread::sleep_for(std::chrono::microseconds(10));
                } else {
                    // 大包稍微等待，避免网络拥塞
                    std::this_thread::sleep_for(std::chrono::microseconds(50));
                }
            }
            });
    }

    tcp::socket socket_;
    int test_data_size_;
    int message_count_;
    std::chrono::steady_clock::time_point start_time_;
};


void run_server(const char* address, const char* port, bool enable_no_delay)
{
    try
    {
        asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::endpoint endpoint = *resolver.resolve(address, port).begin();

        server s(io_context, endpoint, enable_no_delay);

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void run_client(const char* address, const char* port, int test_size, int test_duration_seconds, bool enable_no_delay)
{
    try
    {
        asio::io_context io_context;

        tcp::resolver resolver(io_context);
        tcp::endpoint endpoint = *resolver.resolve(address, port).begin();

        client c(io_context, endpoint, test_size, enable_no_delay);

        auto test_start = std::chrono::steady_clock::now();
        asio::steady_timer timer(io_context, std::chrono::seconds(test_duration_seconds));
        timer.async_wait([&io_context, &c, test_start, test_size](const std::error_code&) {
            auto test_end = std::chrono::steady_clock::now();
            auto total_time = std::chrono::duration_cast<std::chrono::milliseconds>(test_end - test_start).count();
            
            int total_messages = c.get_message_count();
            double throughput = (double)total_messages * test_size * 1000.0 / total_time / 1024 / 1024; // MB/s
            double msg_rate = (double)total_messages * 1000.0 / total_time; // messages/s
            double avg_latency = (double)total_time / total_messages; // ms per message
            
            std::cout << "=== Final Results ===\n";
            std::cout << "Total messages: " << total_messages << "\n";
            std::cout << "Test duration: " << total_time << " ms\n";
            std::cout << "Throughput: " << throughput << " MB/s\n";
            std::cout << "Message rate: " << msg_rate << " msgs/s\n";
            std::cout << "Avg latency: " << avg_latency << " ms/msg\n";
            
            io_context.stop();
        });

        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

void run_benchmark_test(bool enable_no_delay) {
    std::cout << "\n=== Testing with no_delay=" << (enable_no_delay ? "true" : "false") << " ===\n";
    
    // 使用更小的包和更高频率来体现no_delay效果
    std::vector<std::pair<int, std::string>> test_configs = {
        {1, "Very small packets (10 bytes)"},
        {10, "Very small packets (10 bytes)"},      // 极小包，体现Nagle算法影响
        {50, "Small packets (50 bytes)"},          // 小包
        {200, "Medium packets (200 bytes)"},       // 中等包  
        {1000, "Large packets (1000 bytes)"},      // 大包
        {5000, "Very large packets (5000 bytes)"}  // 很大包
    };
    
    int base_port = enable_no_delay ? 12000 : 13000; // 不同配置使用不同端口范围
    
    for (size_t i = 0; i < test_configs.size(); ++i) {
        int size = test_configs[i].first;
        const std::string& desc = test_configs[i].second;
        int port = base_port + i;
        
        std::cout << "\n--- " << desc << " (Port: " << port << ") ---\n";
        
        // 启动服务器
        std::string port_str = std::to_string(port);
        std::thread server_thread(run_server, "127.0.0.1", port_str.c_str(), enable_no_delay);
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 等待服务器启动
        
        std::thread client_thread(run_client, "127.0.0.1", port_str.c_str(), size, 2, enable_no_delay);
        
        client_thread.join();
        server_thread.detach(); // 服务器线程后台运行
        
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 增加等待时间，确保端口释放
    }
}

int main(){
    std::cout << "TCP no_delay Performance Test\n";
    std::cout << "==============================\n";
    
    run_benchmark_test(true);
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    run_benchmark_test(false);
    
    std::cout << "\n=== 总结 ===\n";
    std::cout << "1. no_delay=true:  禁用Nagle算法，适合实时应用，小包延迟更低\n";
    std::cout << "2. no_delay=false: 启用Nagle算法，适合批量传输，可能合并小包\n";
    std::cout << "3. 在本地测试中差异较小，实际网络环境中差异更明显\n";
    std::cout << "4. 对于小包(1-200字节)，no_delay效果最显著\n";
    
    return 0;
}