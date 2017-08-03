#pragma once
#include <boost/asio.hpp>
#include <string>

using namespace boost::asio;
using namespace boost::asio::ip;

class UDPClient {
   public:
    UDPClient(const std::string& sender_ip, const std::string& receiver_ip, unsigned sender_port = 8080,
              unsigned receiver_port = 8080);
    ~UDPClient();
    virtual void run() = 0;
    virtual void do_read() = 0;

   protected:
    std::vector<char> buf;
    io_service ioservice;
    udp::endpoint sender_addr;
    udp::endpoint receiver_addr;
    udp::socket socket;
};
