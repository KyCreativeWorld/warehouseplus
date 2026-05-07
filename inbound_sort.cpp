#include "inbound_sort.h"

void inboundSort(ikeaData& wh, std::string sortBy, size_t stopNum) {
    if (stopNum == 0) stopNum = wh.id.size();
    
    for (int i = 1; i < stopNum; ++i) {
        int keyI = wh.id[i];
        std::string keyN = wh.name[i];
        std::string keyT = wh.type[i];
        double keyP = wh.price[i];
        int j = i - 1;

        while (j >= 0) {
            bool shouldSwap = false;
            if (sortBy == "id") shouldSwap = wh.id[j] > keyI;
            if (sortBy == "name") shouldSwap = wh.name[j] > keyN;
            if (sortBy == "type") shouldSwap = wh.type[j] > keyT;
            if (sortBy == "price") shouldSwap = wh.price[j] > keyP;

            if (!shouldSwap) break;

            wh.id[j + 1] = wh.id[j];
            wh.name[j + 1] = wh.name[j];
            wh.type[j + 1] = wh.type[j];
            wh.price[j + 1] = wh.price[j];

            j--;
        }

        wh.id[j + 1] = keyI;
        wh.name[j + 1] = keyN;
        wh.type[j + 1] = keyT;
        wh.price[j + 1] = keyP;
    }
}