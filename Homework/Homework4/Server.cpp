// Copyright (c) Carson Gooch 2025

/* 
 * File:   Server.cpp
 * 
 */

#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include "Server.h"
using namespace boost::asio;
using namespace boost::asio::ip;

// The default file to return for "/"
const std::string RootFile = "index.html";
    
Server::Server() {
    // Nothing to be done in the constructor (for now).
}

Server::~Server() {
    // Nothing to be done in the destructor.
}

// Implement rest of your methods for your class here. Ensure all of your
// methods are associated with the the Server class!

std::string getFileType(const std::string& fileName) {
    std::string type = "";
    bool dot = false;

    for (size_t i = 0; i < fileName.size(); ++i) {
        if (dot == true) {
            type += fileName[i];
        } else if (fileName[i] == '.') {
            dot = true;
        }
    }
    if (type == "html") {
        return "text/html";
    }
    if (type == "txt") {
        return "text/plain";
    }
    if (type == "png") {
        return "image/png";
    }
    if (type == "jpg") {
        return "image/jpeg";
    }
    return "text/plain";
}

void messagePrinter(std::string& content_text, std::ostream& os, std::string 
    fileStat, const std::string& typeOfFile) {
    os << "HTTP/1.1 " << fileStat << "\r\n" 
    << "Server: SimpleServer\r\n"
    << "Content-Length: " << content_text.size() << "\r\n"
    << "Connection: Close\r\n" 
    << "Content-Type: " << typeOfFile << "\r\n\r\n";
    os << content_text;
}

std::string indexCheck(std::string name, std::string FileRoot) {
    if (name == "/") {
        return FileRoot;
    } else {
        return name;
    }
}

std::string openFile(std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary);
    if (!file) {
        return "The following file was not found: " + fileName + "\n";
    }
    file.seekg(0, std::ios::end);
    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    std::string text(fileSize, '\0');
    file.read(&text[0], fileSize);
    return text;
}

void Server::runServer() {
    io_service service;
    tcp::endpoint point(tcp::v4(), 0);
    tcp::acceptor serve(service, point);
    while (true) {
        tcp::iostream client;
        serve.accept(*client.rdbuf());
        serveClient(client, client);
    }
}

void Server::serveClient(std::istream& is, std::ostream& os) {
    std::string Stat = "200 OK";
    std::string line;
    std::getline(is, line);

    const size_t spc1Pos = line.find(' ');
    const size_t spc2Pos = line.find(' ', spc1Pos + 1);
    const std::string filePath = line.substr(spc1Pos + 1, spc2Pos - 
        spc1Pos - 1);
    std::string name = indexCheck(filePath, RootFile);
    if (!name.empty() && name[0] == '/') {
        name = name.substr(1);
    }
    std::string fileType = getFileType(name);
    std::string text = openFile(name);
    if (text == "The following file was not found: " + name + "\n") {
        Stat = "404 Not Found";
        fileType = "text/plain";
    }

    while (std::getline(is, line) && ((line != "") && (line != "\r"))) {
    }
    messagePrinter(text, os, Stat, fileType);
}
