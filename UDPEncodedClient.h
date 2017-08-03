#pragma once
#include <thread>
#include "BlockQueue.h"
#include "EncodedPackage.h"
#include "Encoder.h"
#include "Serializer.h"
#include "UDPClient.h"

class UDPEncodedClient : public UDPClient {
   public:
    UDPEncodedClient(const Encoder& encoder, const std::string& sender_ip, const std::string& receiver_ip,
                     unsigned sender_port = 8080, unsigned receiver_port = 8080);
    ~UDPEncodedClient();
    virtual void run();
    virtual void do_read();

   private:
    void deserialize();
    void decode();

    Encoder encoder;
    Serializer serializer;
    std::thread deserialize_thd;
    std::thread decode_thd;
    BlockQueue<std::vector<char>> deserialize_Q;
    BlockQueue<std::vector<EncodedPackage>> decode_Q;
    size_t last_ep_index;
    size_t this_ep_index;
};
