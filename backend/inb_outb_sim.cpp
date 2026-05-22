#include "inb_outb_sim.h"
#include <random>

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


void inboundShippment(std::vector<ikeaData>& wh,
                      std::vector<ikeaData>& shipments,
                      int amount,
                      RandomGenerator& randGen) 
{
    for (int i = 0; i < amount; ++i) {
        
        size_t randItemIndex = randGen.randomIndex(shipments.size());

        wh.push_back(shipments[randItemIndex]);
    }
}

void outboundShippment(std::vector<ikeaData>& wh, int amount) {}

void startSim(std::vector<ikeaData>& wh, int minInb, int maxInb, int minOutb, int maxOutb,
              int minInbFeq, int maxInbFeq, int minOutbFeq, int maxOutbFeq) {


            
}