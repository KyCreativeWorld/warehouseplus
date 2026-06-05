#pragma once

#include "ikea_data_struct.h"
#include <random>
#include <vector>
#include <algorithm>
#include <filesystem>

class RandomGenerator {
    private:
        std::mt19937 rng;

    public:
        RandomGenerator() : rng(std::random_device{}()) {}

        size_t randomIndex(size_t maxExclusive) {
            std::uniform_int_distribution<size_t> dist(0, maxExclusive - 1);

            return dist(rng);
        }
};

void binaryInsert(std::vector<ikeaData>& wh, const ikeaData& value);

void inboundShippment(std::vector<ikeaData>& wh, std::vector<ikeaData>& shipments, int amount, RandomGenerator& randGen);
void outboundShippment(std::vector<ikeaData>& wh, std::vector<ikeaData>& shipments, int amount, RandomGenerator& randGen);

// void startSim(std::vector<ikeaData>& wh, int minInb, int maxInb, int minOutb, int maxOutb,
            //   int minInbFeq, int maxInbFeq, int minOutbFeq, int maxOutbFeq);

inline unsigned int numInboundShippments;
inline unsigned int numOutboundShippments;

void deleteItemsUpdate(std::vector<ikeaData>& wh, unsigned int amount);