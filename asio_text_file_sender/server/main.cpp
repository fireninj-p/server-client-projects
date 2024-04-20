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
io_context io;
steady_timer buff(io, asio::chrono::seconds(2));
void start_server() {
    try {
        io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), PORT_NUMBER));
        
        cout << "Server started. Waiting for connections..." << endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            cout << "Connection established with client " << socket.remote_endpoint() << endl;

            array<char, 1024> recv_buffer;
            size_t len = socket.read_some(buffer(recv_buffer));

            cout << "Received data from client: ";
            cout.write(recv_buffer.data(), len);
            cout << endl;

            // Process received data here...

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
