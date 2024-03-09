#include "provinces.h"

int64_t CountPassports(const std::vector<int>& provinces) {
    int64_t conversions = 0;
    std::multiset<int64_t> prov;
    for (size_t i = 0; i < provinces.size(); ++i) {
        prov.emplace(provinces[i]);
    }
    int64_t new_num = 0;
    while (prov.size() > 1) {
        new_num = *prov.begin() + *std::next(prov.begin());
        prov.insert(new_num);
        conversions += new_num;
        prov.erase(prov.begin());
        prov.erase(prov.begin());
    }
    return conversions;
}