#pragma once

#include "EncodedPackage.h"
#include <vector>


class Serializer
{
public:
	Serializer();
	~Serializer();
    std::vector<char> serialize(const EncodedPackage& encodedpackage);
	EncodedPackage deserialize(const std::vector<char>& rawbytes);
	EncodedPackage deserialize(const std::vector<char>& rawbytes, size_t N);
};

