#include "server.h"
#include <iostream>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

server::server(unsigned short port)
    : context{}, acceptor{context, {tcp::v4(), port}}, should_stop{false}, worker{&server::run,
                                                                                  this}
{
}
void server::run()
{
	static size_t request_count = 0;
	while (!should_stop)
	{
		tcp::socket socket{context};
		acceptor.accept(socket);
		std::clog << "Received request#" << ++request_count << " from "
		          << socket.remote_endpoint().address().to_string() << ":"
		          << socket.remote_endpoint().port() << '\n';
		try
		{
			beast::flat_buffer buffer{8192};
			http::request<http::dynamic_body> request;
			http::read(socket, buffer, request);

			http::response<http::dynamic_body> response;
			response.version(request.version());
			response.keep_alive(false);

			if (request.method() == http::verb::get)
			{
				response.result(http::status::ok);
				response.set(http::field::content_type, "application/json");
				response.set(http::field::access_control_allow_origin, "*");
				{
					std::lock_guard<std::mutex> lock{mut};
					beast::ostream(response.body()) << message;
				}
			}
			else
			{
				response.result(http::status::bad_request);
			}

			response.content_length(response.body().size());
			http::write(socket, response);
			std::clog << "Successfully sent response" << '\n';
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error sending response: " << e.what() << '\n';
		}
		catch (...)
		{
			std::clog << "Unknown error while sending response" << '\n';
		}
	}
}
server::~server()
{
	should_stop = true;
	worker.join();
}
void server::set_message(const std::string& new_message)
{
	std::lock_guard<std::mutex> lock{mut};
	message = new_message;
}
