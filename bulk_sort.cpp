#include "bulk_sort.h"

void bulkSort(ikeaData& wh, std::string sortBy, size_t stopNum) {
    if (stopNum == 0) stopNum = wh.id.size();
    
    std::vector<size_t> indices(stopNum);
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
        if (sortBy == "id") return (wh.id.at(a) < wh.id.at(b));
        if (sortBy == "name") return (wh.name.at(a) < wh.name.at(b));
        if (sortBy == "type") return (wh.type.at(a) < wh.type.at(b));
        if (sortBy == "price") return (wh.price.at(a) < wh.price.at(b));
    });

    // Update wh based on indices
}