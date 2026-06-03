#pragma once

#include "ikea_data_struct.h"
#include <random>
#include <vector>

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

void inboundShippment(std::vector<ikeaData>& wh, std::vector<ikeaData>& shipments, int amount, RandomGenerator& randGen);
void outboundShippment(std::vector<ikeaData>& wh, int amount);

// void startSim(std::vector<ikeaData>& wh, int minInb, int maxInb, int minOutb, int maxOutb,
            //   int minInbFeq, int maxInbFeq, int minOutbFeq, int maxOutbFeq);

unsigned int numInboundShippments;
unsigned int numOutboundShippments;

void startDeleteLoop(std::vector<ikeaData>& wh, unsigned int amount);