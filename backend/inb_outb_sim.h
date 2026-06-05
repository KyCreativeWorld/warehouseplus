#pragma once

#include "ikea_data_struct.h"
#include <random>
#include <vector>
#include <algorithm>
#include <filesystem>
#include "nlohmann/json.hpp"

using json = nlohmann::json;



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

void inboundShipment(std::vector<ikeaData>& wh, std::vector<ikeaData>& shipments, int amount, RandomGenerator& randGen);
void outboundShipment(std::vector<ikeaData>& wh, std::vector<ikeaData>& shipments, int amount, RandomGenerator& randGen);

unsigned int runShipments(std::vector<ikeaData>& wh, std::vector<ikeaData>& shipments, json simData, RandomGenerator& randGen);

inline unsigned int numInboundShippments;
inline unsigned int numOutboundShippments;

void deleteItemsUpdate(std::vector<ikeaData>& wh, unsigned int amount);