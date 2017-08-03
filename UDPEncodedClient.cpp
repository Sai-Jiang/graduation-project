#include "UDPEncodedClient.h"
#include <future>
#include "PaddingPackage.h"

UDPEncodedClient::UDPEncodedClient(const Encoder& encoder, const std::string& sender_ip, const std::string& receiver_ip,
                                   unsigned sender_port, unsigned receiver_port)
    : UDPClient(sender_ip, receiver_ip, sender_port, receiver_port),
      encoder(encoder),
      decode_Q(4),
      last_ep_index(0),
      this_ep_index(0) {
    deserialize_thd = std::thread(&UDPEncodedClient::deserialize, this);
    decode_thd = std::thread(&UDPEncodedClient::decode, this);
}

UDPEncodedClient::~UDPEncodedClient() {
    deserialize_thd.join();
    decode_thd.join();
}

void UDPEncodedClient::run() {
    buf.resize(encoder.getl() + 4 * (encoder.getdeg_max() + 1 + 1));
    do_read();
    ioservice.run();
}

void UDPEncodedClient::do_read() {
    std::vector<EncodedPackage> eps;
    while (true) {
        size_t size = socket.receive_from(buffer(buf), sender_addr);
        if (size != 0) {
            deserialize_Q.push(std::vector<char>(buf.begin(), buf.begin() + size));
            // std::cerr << "解序列队列：" << des_Q.size() << std::endl;
        }
    }
}

void UDPEncodedClient::deserialize() {
    std::vector<EncodedPackage> encodedpackages;
    while (true) {
        EncodedPackage encodedpackage(serializer.deserialize(deserialize_Q.pop()));
        this_ep_index = encodedpackage.getindex();
        if (this_ep_index == last_ep_index) {
            encodedpackages.push_back(std::move(encodedpackage));
        } else {
            decode_Q.push(std::move(encodedpackages));
            // std::cerr << "解码队列：" << dec_Q.size() << std::endl;
            encodedpackages.clear();
            encodedpackages.push_back(std::move(encodedpackage));
        }
        last_ep_index = this_ep_index;
    }
}

void UDPEncodedClient::decode() {
    while (true) {
        std::vector<EncodedPackage> encodedpackages(decode_Q.pop());
        // std::cerr << "编码包数量" << encodedpackages.size() << std::endl;
        /*
        for (const auto& ep: encodedpackages) {
            std::cerr << ep << std::endl;
        }
        */
        PaddingPackage paddingpackage(encoder.decode(encodedpackages));
        std::pair<char*, size_t> data(paddingpackage.getRawData());
        write(STDOUT_FILENO, data.first, data.second);
    }
}
