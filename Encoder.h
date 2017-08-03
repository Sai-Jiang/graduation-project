#pragma once
#include <map>
#include <random>
#include <utility>
#include <vector>
#include "RobustSolitonDistribution.h"

class EncodedPackage;
class PaddingPackage;

class Encoder {
   public:
    Encoder(const unsigned k = 100, const unsigned m = 200, const unsigned l = 512,
            const std::vector<std::pair<unsigned, double>>& pdf = RobustSolitonDistribution().getpdf());
    ~Encoder();

    std::vector<EncodedPackage> encode(const PaddingPackage& paddingpackage);
    EncodedPackage sprayOneDrop(const PaddingPackage& paddingpackage);
    PaddingPackage decode(const std::vector<EncodedPackage>& encodedpackages);
    unsigned getk() const;
    unsigned getm() const;
    unsigned getl() const;
    unsigned getdeg_max() const;

   private:
    unsigned popd();
    std::vector<unsigned> choose(unsigned d);  //��k�����������ѡȡd����

    std::default_random_engine engine;
    unsigned k;
    unsigned m;  //(m - k)/k�����뿪��
    unsigned l;  //������ŵĳ���
    std::vector<std::pair<unsigned, double>> pdf;
    std::vector<std::pair<unsigned, double>> cdf;
};
