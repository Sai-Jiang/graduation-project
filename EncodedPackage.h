#pragma once
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
	unsigned getd();
	unsigned getindex();

private:
	unsigned index; //����ԭ��������
	unsigned d; //�˱�����Ķ�
    std::vector<unsigned> adjacency; //�ڽӹ�ϵ
    std::vector<char> data; //����������
};

