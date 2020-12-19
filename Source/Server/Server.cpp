#include "Server.h"

#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <memory>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

namespace
{
	asio::io_context context;
	std::unique_ptr<tcp::acceptor> acceptor;
}

void init_server(const u16 port)
{
	acceptor = std::make_unique<tcp::acceptor>(context, tcp::endpoint{tcp::v4(), port});
}

void handle_requests()
{
	// ===================== WHAT IS THIS =====================
	tcp::socket socket{context};
	beast::flat_buffer buffer{8192};
	http::request<http::dynamic_body> request;

	acceptor->accept(socket);
	http::read(socket, buffer, request);

	http::response<http::dynamic_body> response;
	response.version(request.version());
	response.keep_alive(false);
	// ===================== WHAT IS THIS =====================

	if (request.method() == http::verb::get)
	{
		response.result(http::status::ok);
		response.set(http::field::content_type, "application/json");
		beast::ostream(response.body()) << "{\"test\": \"Hello, world!\"}"; // why create an ostream??
	}
	else
	{
		response.result(http::status::bad_request);
	}

	response.content_length(response.body().size()); // why? what does this do
	http::write(socket, response);
}
