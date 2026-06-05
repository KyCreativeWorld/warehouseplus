#include "bulk_sort.h"

void bulkSort(std::vector<ikeaData>& wh) {
    std::sort(
        wh.begin(),
        wh.end(),
        [](const ikeaData& a, const ikeaData& b) {
            return a.id < b.id;
        });
}