#include "Encoder.h"
#include <time.h>
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <random>
#include <set>
#include "EncodedPackage.h"
#include "PaddingPackage.h"

Encoder::Encoder(const unsigned k, const unsigned m, const unsigned l,
                 const std::vector<std::pair<unsigned, double>>& pdf)
    : k(k), m(m), l(l), pdf(pdf) {
    srand(time(NULL));
    std::sort(this->pdf.begin(), this->pdf.end(),
              [](const std::pair<unsigned, double> i, const std::pair<unsigned, double> j) { return i < j; });
    for (auto iter = this->pdf.cbegin(); iter != this->pdf.cend(); iter++) {
        cdf.push_back(std::make_pair(
            iter->first,
            accumulate(this->pdf.cbegin(), iter + 1, 0.0, [](double partialResult, std::pair<unsigned, double> next) {
                return partialResult + next.second;
            })));
    }
}

Encoder::~Encoder() {}

std::vector<EncodedPackage> Encoder::encode(const PaddingPackage& paddingpackage) {
    std::vector<EncodedPackage> vec;
    for (size_t i = 0; i < m; i++) {
        vec.push_back(sprayOneDrop(paddingpackage));
    }
    return vec;
}

EncodedPackage Encoder::sprayOneDrop(const PaddingPackage& paddingpackage) {
    EncodedPackage encodedpackage;
    encodedpackage.index = paddingpackage.index;
    encodedpackage.d = popd();
    encodedpackage.adjacency = choose(encodedpackage.d);
    encodedpackage.data = std::vector<char>(l);

    for (unsigned index : encodedpackage.adjacency) {
        for (size_t i = 0; i < l; i++) {
            encodedpackage.data[i] ^= paddingpackage.pdata[index * l + i];
        }
    }
    // std::cerr << ep << std::endl;
    return encodedpackage;
}

PaddingPackage Encoder::decode(const std::vector<EncodedPackage>& encodedpackages) {
    assert(encodedpackages.size() <= m);
    PaddingPackage paddingpackage(*this);
    std::vector<unsigned> eps_index;
    for (size_t i = 0; i < encodedpackages.size(); i++) {
        eps_index.push_back(i);
    }

    auto compare = [&encodedpackages](const unsigned i, const unsigned j) { return encodedpackages.at(i) > encodedpackages.at(j); };
    while (!eps_index.empty()) {
        std::make_heap(eps_index.begin(), eps_index.end(), compare);
        pop_heap(eps_index.begin(), eps_index.end(), compare);
        EncodedPackage this_ep = encodedpackages.at(eps_index.back());
        if (this_ep.d == 1) {
            unsigned index = this_ep.adjacency.front();
            for (unsigned ep_index : eps_index) {
                EncodedPackage that_ep = encodedpackages.at(ep_index);
                auto iter = std::find(that_ep.adjacency.cbegin(), that_ep.adjacency.cend(), index);
                if (that_ep.adjacency.cend() != iter) {
                    if (this_ep == that_ep) {
                        std::copy(this_ep.data.cbegin(), this_ep.data.cend(), paddingpackage.pdata.begin() + index * l);
                    } else {
                        that_ep.d--;
                        that_ep.adjacency.erase(iter);
                        for (size_t j = 0; j < l; j++) {
                            that_ep.data[j] ^= this_ep.data[j];
                        }
                    }
                }
            }
            eps_index.pop_back();
        } else {
            break;
        }
    }

    size_t size = *(uint32_t*)paddingpackage.pdata.data();
    paddingpackage.rsize = size ? size : (paddingpackage.psize - 4);

    return paddingpackage;
}

std::vector<unsigned> Encoder::choose(unsigned d) {
    assert(d <= k);
    std::vector<unsigned> v;
    unsigned remain = k;
    unsigned select = d;
    for (size_t i = 0; i < k; i++) {
        if (rand() % remain < select) {
            v.push_back(i);
            select--;
        }
        remain--;
    }
    return v;
}

unsigned Encoder::popd() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<double> distribution;
    double random = distribution(engine);
    for (const auto& c : cdf) {
        if (random < c.second) return c.first;
    }
    return 0;
}

unsigned Encoder::getk() const { return k; }
unsigned Encoder::getm() const { return m; }
unsigned Encoder::getl() const { return l; }
unsigned Encoder::getdeg_max() const { return pdf.back().first; }
