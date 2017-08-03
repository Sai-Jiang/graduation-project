#include "UDPEncodedServer.h"
#include <unistd.h>
#include <cstddef>
#include <future>
#include "EncodedPackage.h"
#include "PaddingPackage.h"

UDPEncodedServer::UDPEncodedServer(const Encoder& encoder, const std::string& sender_ip, const std::string& receiver_ip,
                                   unsigned sender_port, unsigned receiver_port)
    : UDPServer(sender_ip, receiver_ip, sender_port, receiver_port), encoder(encoder), Q(1) {
    encode_thd = std::thread(&UDPEncodedServer::encodeAndSend, this);
}

UDPEncodedServer::~UDPEncodedServer() { encode_thd.join(); }

void UDPEncodedServer::run() {
    buf.resize(encoder.getk() * encoder.getl() - 4);
    do_read();
    ioservice.run();
}

void UDPEncodedServer::do_read() {
    while (true) {
        size_t size = read(STDIN_FILENO, buf.data(), buf.size());
        if (size > 0) {
            write(STDOUT_FILENO, buf.data(), size);
            PaddingPackage paddingpackage(encoder, buf.data(), size);
            Q.push(paddingpackage);
            // std::cerr << "编码队列：" << Q.size() << std::endl;
        }
    }
}

void UDPEncodedServer::encodeAndSend() {
    while (true) {
        PaddingPackage paddingpackage(Q.pop());
        for (size_t i = 0; i < encoder.getm(); i++) {
            EncodedPackage encodedpackage(encoder.sprayOneDrop(paddingpackage));
            // std::cerr << ep << std::endl;
            socket.send_to(buffer(serializer.serialize(encodedpackage)), receiver_addr);
            usleep(100);
        }
    }
}
