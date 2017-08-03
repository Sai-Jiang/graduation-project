#pragma once

#include <vector>
#include <map>

class Encoder;
class PaddingPackage
{
	friend class Encoder;
public:
	PaddingPackage(const Encoder& e);
	PaddingPackage(const Encoder& e, const std::vector<char>& rdata);
	PaddingPackage(const Encoder& e, const char* rdata, size_t rsize);
	~PaddingPackage();
    std::pair<char*, size_t> getRawData();
    size_t getindex();


private:
	static size_t count; //ԭʼ���ݵı��
    size_t index;
	size_t rsize; //ԭʼ���ݴ�С
	size_t psize; //�������ӳ���ͷ������ݴ�С
    std::vector<char> pdata; //����������
};

