#include <iostream>

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00

#endif // _WIN32
#define ASIO_STANDALONE
#include <fstream>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <unordered_map>

using namespace std;
using namespace asio;
using namespace asio::ip;

constexpr unsigned short PORT_NUMBER = 3333;


//asio::io_context io;
io_context io;
steady_timer t(io, asio::chrono::seconds(10));
steady_timer buff(io, asio::chrono::seconds(2));

void send_text_document() {
    try {
        io_context io_context;
        tcp::socket socket(io_context);
        socket.connect(tcp::endpoint(address::from_string("127.0.0.1"), PORT_NUMBER));

        cout << "Connected to server." << endl;

        ifstream file("text_document.txt");
        if (!file.is_open()) {
            cerr << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            write(socket, buffer(line + "\n"));
            
        }
        file.close();

        cout << "Text document sent successfully." << endl;

        socket.close();
        
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    while (true) {
        send_text_document();
        t.wait();
        //this_thread::sleep_for(chrono::minutes(1));
    }
    return 0;
}
