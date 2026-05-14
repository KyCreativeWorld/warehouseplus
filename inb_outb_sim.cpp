#include "inb_outb_sim.h"

void inboundShippment(ikeaData& wh, int amount) {
    unsigned int i;
    for (i = 0; i < amount; ++i) {
        unsigned int randItemIndex = rand() % wh.id.size();

        
    }
}

void outboundShippment(ikeaData& wh, int amount);

void startSim(ikeaData wh, int minInb, int maxInb, int minOutb, int maxOutb,
              int minInbFeq, int maxInbFeq, int minOutbFeq, int maxOutbFeq) {


            
}