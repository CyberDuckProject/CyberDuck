#ifndef SERVER_H
#define SERVER_H

#include "boost/asio.hpp"
#include "boost/beast.hpp"
#include <atomic>
#include <memory>
#include <mutex>

class server
{
    boost::asio::io_context context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::atomic_bool should_stop;
    std::thread worker;
    std::string message;
    std::function<std::string()> provider;
	mutable std::mutex mut;
public:
    explicit server(const std::function<std::string()>& new_provider, unsigned short port = 80);
	~server();

	void set_message_provider(const std::function<std::string()>& new_provider);
private:
    void run();
};

#endif
