#pragma once
#include <vector>
#include <iostream>

using std::vector;
using std::ostream;

class EncodedPackage
{
	friend class Encoder;
	friend class Serializer;
	friend bool operator==(const EncodedPackage& lep, const EncodedPackage& rep);
	friend bool operator!=(const EncodedPackage& lep, const EncodedPackage& rep);
	friend bool operator<(const EncodedPackage& lep, const EncodedPackage& rep);
	friend bool operator>(const EncodedPackage& lep, const EncodedPackage& rep);
	friend ostream& operator<<(ostream& os, const EncodedPackage& ep);

public:
	EncodedPackage();
	~EncodedPackage();
	int getd();
	int getindex();

private:
	int index; //����ԭ��������
	int d; //�˱�����Ķ�
	vector<int> adjacency; //�ڽӹ�ϵ
	vector<char> data; //����������
};

