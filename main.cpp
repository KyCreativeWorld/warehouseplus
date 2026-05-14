#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ikea_data_struct.h"
#include "inbound_sort.h"
#include "read_csv_file.h"

int main() {
    std::string dataFileName;

    getline(std::cin, dataFileName);

    ikeaData warehouse;
    ikeaData shipmentData;
    readCSVFile(warehouse, shipmentData, dataFileName);

    // inboundSort(warehouse, "price");

    unsigned int printStop = 10;
    std::cout << std::endl << "ShipmentData (size: " << shipmentData.id.size() << "):" << std::endl;
    if (shipmentData.id.size() < 1) { std::cout << "NO ITEMS IN SHIPMENTDATA!!" << std::endl; }
    else {
    for (unsigned int i = 0; i < printStop; ++i) {
        std::cout << shipmentData.id.at(i) << ",{"
              << shipmentData.name.at(i) << "},["
              << shipmentData.type.at(i) << "],"
              << shipmentData.price.at(i) << " >"
              << std::endl;
    }
    }


    std::cout << std::endl << "Warehouse (size: " << warehouse.id.size() << "):" << std::endl;
    if (warehouse.id.size() < 1) { std::cout << "NO ITEMS IN WAREHOUSE!!" << std::endl; }
    else {
    for (unsigned int i = 0; i < printStop; ++i) {
        std::cout << warehouse.id.at(i) << ",{"
              << warehouse.name.at(i) << "},["
              << warehouse.type.at(i) << "],"
              << warehouse.price.at(i) << " >"
              << std::endl;
    }
    }

    return 0;
}