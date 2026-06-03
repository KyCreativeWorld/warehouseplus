#include "inb_outb_sim.h"
#include <random>


void inboundShippment(std::vector<ikeaData>& wh,
                      std::vector<ikeaData>& shipments,
                      int amount,
                      RandomGenerator& randGen) 
{
    for (int i = 0; i < amount; ++i) {
        
        size_t randItemIndex = randGen.randomIndex(shipments.size());

        wh.push_back(shipments[randItemIndex]);

        numInboundShippments++;
    }
}

void outboundShippment(std::vector<ikeaData>& wh, int amount) {}

// void startSim(std::vector<ikeaData>& wh, int minInb, int maxInb, int minOutb, int maxOutb,
//               int minInbFeq, int maxInbFeq, int minOutbFeq, int maxOutbFeq) {
    // while (running)
    // pull from simulator_info.json
    // if (delete(new_data_available)) (check main.cpp for example of this)
    // switch
    //  case 0
    //      simOn = false
    //  case 1
    //      simOn = true
    //
    //  if (simOn)
    //    wait random time based on timer
    //    call inb
    //    call outb
    //  else
    //    wait 0.25s
    // repeat

            
// }

void startDeleteLoop(std::vector<ikeaData>& wh, unsigned int amount) {
    bool delLoopRunning = true;
    
    while (delLoopRunning) {
        if (std::filesystem::remove("backend/delete_items.txt")) {
            for (unsigned int i = 0; i < amount; i++) {
                wh.erase(wh.end() - amount, wh.end());
            }
        }
        
        if (!std::filesystem::exists("backend/simulator_info.json")) delLoopRunning = false;
    }
}