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
	mutable std::mutex mut;
public:
    explicit server(unsigned short port = 80);
	~server();
	void set_message(const std::string& new_message);
private:
    void run();
};

#endif
