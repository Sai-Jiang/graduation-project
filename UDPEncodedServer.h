#pragma once
#include <thread>
#include "BlockQueue.h"
#include "Encoder.h"
#include "Serializer.h"
#include "UDPServer.h"

class UDPEncodedServer : public UDPServer {
   public:
    UDPEncodedServer(const Encoder& encoder, const std::string& sender_ip, const std::string& receiver_ip,
                     unsigned sender_port = 8080, unsigned receiver_port = 8080);
    ~UDPEncodedServer();
    virtual void run();
    virtual void do_read();

   private:
    void encodeAndSend();

    Encoder encoder;
    Serializer serializer;
    std::thread encode_thd;
    BlockQueue<PaddingPackage> Q;
};
