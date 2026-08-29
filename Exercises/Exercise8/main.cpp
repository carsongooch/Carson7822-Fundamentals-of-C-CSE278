/* 
 * A silly web-server.  
 * 
 * The web-server performs the following tasks:
 * 
 *     1. Accepts connection from a client.
 *     2. Prints all the headers sent by a client & ignores them.
 *     3. Simply send a message back to the client.
 * 
 * Copyright (C) goochcj@miamioh.edu
 */

#include <boost/asio.hpp>
#include <iostream>
#include <string>

// The simple HTML message to be sent to the client. Instead we could
// also copy data from a file (see slides on copying lines...)
const std::string msg = "<html>\n"
    "<body>\n"
    "<h1>Testing</h1><n"
    "<p> a simple para<\p>"
    "</body>\n"
    "</html>\n";


/**
 * Process HTTP request (from first line & headers) and
 * provide suitable HTTP response back to the client.
 * Recollect HTTP request has many lines. e.g:
 * 
 * GET /~raodm/test.html HTTP/1.1
 * Host: ceclnx01.cec.miamioh.edu
 * Connection: Close
 * 
 * @param is The input stream to read data from client.
 * @param os The output stream to send data to client.
 */
void serveClient(std::istream& is, std::ostream& os) {
    // First extract request line from client
    // The line is in the form GET Path_to_file HTTP/1.1
    std::string line;
    std::getline(is, line);

    // Ideally server returns contents of file requested by user
    std::cout << line << std::endl;  // print request line.
    
    // Now modify the code to extract the 2nd word from line to
    // determine the file name! Use line.find(' ', indexPos) method to
    // extract the Path_to_file and print it.
    const size_t spc1Pos = line.find(' ');
    const size_t spc2Pos = line.find(' ', spc1Pos + 1);
    const std::string filePath = line.substr(spc1Pos + 1, spc2Pos - 
        spc1Pos - 1);
    std::cout << "File path: " << filePath << std::endl;

    // Read headers from client and print them. Remember headers end
    // with a blank line. In HTTP blank lines can simply be "\r". This
    // simple server does not really process client headers (real
    // server would)
    while (std::getline(is, line) && ((line != "") && (line != "\r"))) {
        std::cout << line << std::endl;
    }

    // Send a fixed HTTP response back to the client.
    os << "HTTP/1.1 200 OK\r\n"
       << "Server: SimpleServer\r\n"
       << "Content-Length: " << msg.size() << "\r\n"
       << "Connection: Close\r\n"
       << "Content-Type: text/html\r\n\r\n";

    // Instead of writing a simple message we could copy data
    // from a file (line-by-line as shown in lecture slides) to
    // the os (the output stream) to send file contents to client.
    os << msg;
}

// ----------------------------------------------------------------
//   DO  NOT  MODIFY  CODE  BELOW  THIS  LINE
// ----------------------------------------------------------------

/*
 * The main method that performs the basic task of accepting connections
 * from the user.
 */
int main(int argc, char** argv) {
    // Setup a server socket to accept connections on the socket
    using namespace boost::asio;
    using namespace boost::asio::ip;
    io_service service;
    // Create end point. 0 == Pick any free port.
    tcp::endpoint myEndpoint(tcp::v4(), 0);
    // Create a socket that accepts connections
    tcp::acceptor server(service, myEndpoint);
    std::cout << "Listening on port " << server.local_endpoint().port()
              << std::endl;
    // Process client connections one-by-one...forever
    while (true) {
        tcp::iostream client;
        // Wait for a client to connect
        server.accept(*client.rdbuf());
        // Process information from client.
        serveClient(client, client);
    }
    return 0;
}

