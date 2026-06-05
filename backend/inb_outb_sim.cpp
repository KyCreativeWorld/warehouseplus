#include "inb_outb_sim.h"
#include <filesystem>
#include <random>
#include <vector>
#include <algorithm>
#include <filesystem>

void inboundShipment(std::vector<ikeaData>& wh,
                      std::vector<ikeaData>& shipments,
                      int amount,
                      RandomGenerator& randGen) 
{
    for (int i = 0; i < amount; ++i) {        
        size_t randItemIndex = randGen.randomIndex(shipments.size());

        binaryInsert(wh, shipments[randItemIndex]);  
        
        numInboundShippments++;
    }
}

void outboundShipment(std::vector<ikeaData>& wh,
                       std::vector<ikeaData>& shipments,
                       int amount,
                       RandomGenerator& randGen)
{
    for (int i=0; i < amount; ++i) {
        size_t randItemIndex = randGen.randomIndex(wh.size());

        shipments.push_back(wh[randItemIndex]);
        wh.erase(wh.begin() + randItemIndex);

        numOutboundShippments++;
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

int deleteItemsUpdate(std::vector<ikeaData>& wh, unsigned int amount) {
    if (std::filesystem::remove("backend/delete_items.txt")) {
        wh.erase(wh.end() - amount, wh.end());

        return 1;
    } else {
        return -1;
    }
}

int putItemsOnSale(std::vector<ikeaData>& wh, unsigned int amount) {
    if (std::filesystem::remove("backend/put_items_on_sale.txt")) {
        for (unsigned int i = 0; i < amount; i++) {
            wh.at(i).price = wh.at(i).price * 2;
        }

        return 1;
    } else {
        return -1;
    }
}



unsigned int runShipments(std::vector<ikeaData>& wh, std::vector<ikeaData>& shipments, json simData, RandomGenerator& randGen) {
    int inbAmount = simData["sim_inbound_min"].get<int>() + randGen.randomIndex(simData["sim_inbound_max"].get<int>() - simData["sim_inbound_min"].get<int>() + 1);
    int outbAmount = simData["sim_outbound_min"].get<int>() + randGen.randomIndex(simData["sim_outbound_max"].get<int>() - simData["sim_outbound_min"].get<int>() + 1);

    inboundShipment(wh, shipments, inbAmount, randGen);
    outboundShipment(wh, shipments, outbAmount, randGen);

    return simData["sim_timer_min"].get<int>() + randGen.randomIndex(simData["sim_timer_max"].get<int>() - simData["sim_timer_min"].get<int>() + 1);
}