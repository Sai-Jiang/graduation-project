#pragma once

#include <stdint.h>
#include <vector>
#include <iostream>

class EncodedPackage
{
	friend class Encoder;
	friend class Serializer;
	friend bool operator==(const EncodedPackage& lep, const EncodedPackage& rep);
	friend bool operator!=(const EncodedPackage& lep, const EncodedPackage& rep);
	friend bool operator<(const EncodedPackage& lep, const EncodedPackage& rep);
	friend bool operator>(const EncodedPackage& lep, const EncodedPackage& rep);
	friend std::ostream& operator<<(std::ostream& os, const EncodedPackage& ep);

public:
	EncodedPackage();
	~EncodedPackage();
	uint32_t getd();
	uint32_t getindex();

private:
	uint32_t index; //所属原包的索引
	uint32_t d; //此编码包的度
    std::vector<uint32_t> adjacency; //邻接关系
    std::vector<char> data; //编码后的数据
};

