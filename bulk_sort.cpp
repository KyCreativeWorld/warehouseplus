#include "bulk_sort.h"

void bulkSort(ikeaData& wh, std::string sortBy, size_t stopNum) {
    if (stopNum == 0) stopNum = wh.id.size();
    
    std::vector<size_t> indices(stopNum);
    std::iota(indices.begin(), indices.end(), 0);

    std::sort(indices.begin(), indices.end(), [&](size_t a, size_t b) {
        if (sortBy == "id") {
            std::sort(indices.begin(), indices.end(),
                [&](size_t a, size_t b) {
                    return wh.id[a] < wh.id[b];
                });
            }
        else if (sortBy == "name") {
            std::sort(indices.begin(), indices.end(),
                [&](size_t a, size_t b) {
                    return wh.name[a] < wh.name[b];
                });
            }
        else if (sortBy == "type") {
            std::sort(indices.begin(), indices.end(),
                [&](size_t a, size_t b) {
                    return wh.type[a] < wh.type[b];
                });
            }
        else if (sortBy == "price") {
            std::sort(indices.begin(), indices.end(),
                [&](size_t a, size_t b) {
                    return wh.price[a] < wh.price[b];
                });
            }

    });
}

void applyPermutation(ikeaData& wh, std::vector<size_t>& indices) {
    size_t n = indices.size();

    for (size_t i = 0; i < n; ++i) {

        if (indices[i] == i)
            continue;
        
        size_t current = i;

        int tempId = wh.id[i];
        std::string tempName = std::move(wh.name[i]);
        std::string tempType = std::move(wh.type[i]);
        double tempPrice = wh.price[i];

        while (indices[current] != i) {
            size_t next = indices[current];

            wh.id[current] = wh.id[next];
            wh.name[current] = std::move(wh.name[next]);
            wh.type[current] = std::move(wh.type[next]);
            wh.price[current] = wh.price[next];


            indices[current] = current;

            current = next;
        }

        wh.id[current] = tempId;
        wh.name[current] = std::move(tempName);
        wh.type[current] = std::move(tempType);
        wh.price[current] = tempPrice;

        indices[current] = current;
    }
}