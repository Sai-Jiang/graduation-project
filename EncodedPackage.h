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
	uint32_t index; //����ԭ��������
	uint32_t d; //�˱�����Ķ�
    std::vector<uint32_t> adjacency; //�ڽӹ�ϵ
    std::vector<char> data; //����������
};

