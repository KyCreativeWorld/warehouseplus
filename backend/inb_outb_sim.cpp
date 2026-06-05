#include "inb_outb_sim.h"
#include <filesystem>
#include <random>
#include <vector>
#include <algorithm>
#include <filesystem>

void inboundShippment(std::vector<ikeaData>& wh,
                      std::vector<ikeaData>& shipments,
                      int amount,
                      RandomGenerator& randGen) 
{
    for (int i = 0; i < amount; ++i) {        
        size_t randItemIndex = randGen.randomIndex(shipments.size());

        binaryInsert(wh, shipments[randItemIndex]);        
    }
}

void outboundShippment(std::vector<ikeaData>& wh,
                       std::vector<ikeaData>& shipments,
                       int amount,
                       RandomGenerator& randGen)
{
    for (int i=0; i < amount; ++i) {
        size_t randItemIndex = randGen.randomIndex(shipments.size());

        wh.push_back(shipments[randItemIndex]);

        numInboundShippments++;
    }
}

void binaryInsert(std::vector<ikeaData>& wh, const ikeaData& value) {
    auto pos = std::lower_bound(
        wh.begin(),
        wh.end(),
        value.id,
        [](const ikeaData& item, int id) {
            return item.id < id;
        }
    );
    
    wh.insert(pos, value);
}

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

void deleteItemsUpdate(std::vector<ikeaData>& wh, unsigned int amount) {
    if (std::filesystem::remove("backend/delete_items.txt")) {
        for (unsigned int i = 0; i < amount; i++) {
            wh.erase(wh.end() - amount, wh.end());
        }
    }
}