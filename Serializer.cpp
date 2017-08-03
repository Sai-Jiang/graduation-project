#include "Serializer.h"
#include <algorithm>
#include <cassert>
#include <cstdint>

Serializer::Serializer() {}

Serializer::~Serializer() {}

std::vector<char> Serializer::serialize(const EncodedPackage& encodedpackage) {
    std::vector<char> rawbytes;
    char c[4];

    *(uint32_t*)c = encodedpackage.index;
    rawbytes.insert(rawbytes.end(), c, c + 4);

    *(uint32_t*)c = encodedpackage.d;
    rawbytes.insert(rawbytes.end(), c, c + 4);

    for (size_t i = 0; i < encodedpackage.d; i++) {
        *(uint32_t*)c = encodedpackage.adjacency[i];
        rawbytes.insert(rawbytes.end(), c, c + 4);
    }

    rawbytes.insert(rawbytes.end(), encodedpackage.data.begin(), encodedpackage.data.end());

    return rawbytes;
}

EncodedPackage Serializer::deserialize(const std::vector<char>& rawbytes) {
    assert(rawbytes.size() >= 4 * 2);
    EncodedPackage encodedpackage;

    encodedpackage.index = *(uint32_t*)rawbytes.data();

    encodedpackage.d = *(uint32_t*)(rawbytes.data() + 4);

    for (size_t i = 0; i < encodedpackage.d; i++) {
        unsigned d = *(uint32_t*)(rawbytes.data() + 4 * (2 + i));
        encodedpackage.adjacency.push_back(d);
    }

    encodedpackage.data.insert(encodedpackage.data.end(), rawbytes.begin() + 4 * (2 + encodedpackage.d), rawbytes.end());

    return encodedpackage;
}
