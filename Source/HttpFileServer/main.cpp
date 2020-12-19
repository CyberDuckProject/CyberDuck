#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/filesystem.hpp>
#include <cstdlib>
#include <iostream>

namespace fs = boost::filesystem;
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = boost::asio::ip::tcp;

std::string read_file(const fs::path& path)
{
	std::ifstream in(path.c_str(), std::ios::in | std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return contents;
	}
	else
	{
		return "";
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << fs::path(argv[0]).filename() << " path/to/served/directory";
		return EXIT_FAILURE;
	}
	fs::path served_directory = argv[1];

	net::io_context context;
	tcp::acceptor acceptor{context, {tcp::v4(), 43543}};

	while (true)
	{
		try
		{
			tcp::socket socket{context};
			beast::flat_buffer buffer{8192};
			http::request<http::dynamic_body> request;

			acceptor.accept(socket);
			http::read(socket, buffer, request);

			http::response<http::dynamic_body> response;
			response.version(request.version());
			response.keep_alive(false);

			fs::path requested_file =
			    request.target().substr(1, request.target().size() - 1).to_string();
			requested_file = served_directory / requested_file;
			switch (request.method())
			{
			case http::verb::get:
				if (fs::exists(requested_file))
                {
					response.result(http::status::ok);
					response.set(http::field::content_type, "text/plain");
					beast::ostream(response.body()) << read_file(requested_file);
				}
				else
                {
                    response.result(http::status::bad_request);
                    response.set(http::field::content_type, "text/plain");
                    beast::ostream(response.body()) << "Requested file cannot be served\r\n";
				}
				break;
			default:
				response.result(http::status::bad_request);
				response.set(http::field::content_type, "text/plain");
				beast::ostream(response.body()) << "Verb GET must be used\r\n";
			}

			response.content_length(response.body().size());
			http::write(socket, response);
		}
		catch (const std::exception& e)
		{
			std::cerr << "Error: " << e.what() << '\n';
		}
	}
}