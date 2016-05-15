#pragma once

#include <vector>
#include <map>
using std::vector;
using std::pair;
using std::make_pair;

class Encoder;

class PaddingPackage
{
	friend class Encoder;
public:
	PaddingPackage(const Encoder& e);
	PaddingPackage(const Encoder& e, const vector<char>& rdata);
	PaddingPackage(const Encoder& e, char* rdata, int rsize);
	~PaddingPackage();
	pair<char*, int> getRawData();


private:
	static int index; //ԭʼ���ݵı��
	int rsize; //ԭʼ���ݴ�С
	int psize; //�������ӳ���ͷ������ݴ�С
	vector<char> pdata; //����������
};

