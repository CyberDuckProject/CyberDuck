#include "server.h"
#include <spdlog/spdlog.h>
#include <utility>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

server::server(std::function<std::string()> new_provider, u16 port)
    : context{}, acceptor{context, {tcp::v4(), port}},
      should_stop{false}, worker{&server::run, this}, provider{std::move(new_provider)}
{
}

server::~server()
{
	should_stop = true;
	worker.join();
}

void server::set_message_provider(const std::function<std::string()>& new_provider)
{
	std::lock_guard<std::mutex> lock{mut};
	provider = new_provider;
}

void server::run()
{
	static size_t request_count = 0;
	while (!should_stop)
	{
		tcp::socket socket{context};
		acceptor.accept(socket);
		spdlog::debug("Received request #{} from {}:{}", ++request_count,
		              socket.remote_endpoint().address().to_string(),
		              socket.remote_endpoint().port());
		try
		{
			beast::flat_buffer buffer{8192};
			http::request<http::dynamic_body> request;
			http::read(socket, buffer, request);

			http::response<http::dynamic_body> response;
			response.version(request.version());
			response.keep_alive(false);

			if (request.method() == http::verb::get && request.target() == "/environment")
			{
				response.result(http::status::ok);
				response.set(http::field::content_type, "application/json");
				response.set(http::field::access_control_allow_origin, "*");
				{
					std::lock_guard<std::mutex> lock{mut};
					beast::ostream(response.body()) << provider();
				}
			}
			else
			{
				response.result(http::status::bad_request);
			}

			response.content_length(response.body().size());
			http::write(socket, response);
			spdlog::debug("Successfully sent response");
		}
		catch (const std::exception& e)
		{
			spdlog::error("Error sending response: {}", e.what());
		}
		catch (...)
		{
			spdlog::error("Unknown error while sending response");
		}
	}
}
