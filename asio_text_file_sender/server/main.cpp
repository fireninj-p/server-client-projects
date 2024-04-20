#include <iostream>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00

#endif // _WIN32
#define ASIO_STANDALONE

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <unordered_map>


using namespace std;
using namespace asio;
using namespace asio::ip;

constexpr unsigned short PORT_NUMBER = 3333;

void start_server() {
    try {
        io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT_NUMBER));

        cout << "Server started. Waiting for connections..." << endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            cout << "Connection established with client " << socket.remote_endpoint() << endl;

            stringstream received_data;
            asio::error_code error;

            // Read data from the socket until there's no more data to read
            while (true) {
                array<char, 1024> recv_buffer;
                size_t len = socket.read_some(buffer(recv_buffer), error);
                if (error == asio::error::eof)
                    break; // Connection closed by the client

                received_data.write(recv_buffer.data(), len);

                // Check for end-of-data marker
                string received_str = received_data.str();
                size_t pos = received_str.find("END_OF_DATA_MARKER");
                if (pos != string::npos) {
                    // Found end-of-data marker, stop reading
                    received_data.str(received_str.substr(0, pos)); // Remove marker from received data
                    break;
                }
            }

            cout << "Received data from client: \n" << received_data.str() << endl;

            socket.close();
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    start_server();
    return 0;
}
