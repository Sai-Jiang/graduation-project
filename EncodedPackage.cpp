#include "EncodedPackage.h"

EncodedPackage::EncodedPackage() {}

EncodedPackage::~EncodedPackage() {}

bool operator==(const EncodedPackage& lep, const EncodedPackage& rep) {
    return lep.index == rep.index && lep.d == rep.d && lep.adjacency == rep.adjacency;
}

bool operator!=(const EncodedPackage& lep, const EncodedPackage& rep) { return !(lep == rep); }

bool operator<(const EncodedPackage& lep, const EncodedPackage& rep) {
    return lep.d < rep.d || lep.adjacency < rep.adjacency;
}

bool operator>(const EncodedPackage& lep, const EncodedPackage& rep) { return lep.d > rep.d; }

std::ostream& operator<<(std::ostream& os, const EncodedPackage& ep) {
    os << ep.index << " " << ep.d;
    for (unsigned d : ep.adjacency) {
        os << " " << d;
    }
    return os;
}

uint32_t EncodedPackage::getd() { return d; }

uint32_t EncodedPackage::getindex() { return index; }
