#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "backend/nlohmann/json.hpp"
#include "backend/ikea_data_struct.h"
#include "backend/inbound_sort.h"
#include "backend/read_csv_file.h"

using json = nlohmann::json;

int main() {
    std::ifstream dataFile("config.txt");

    json configData;
    try {
        dataFile >> configData;
    } catch (const json::parse_error& e) {
        std::cerr << "JSON Parsing Error: " << e.what() << std::endl;
        dataFile.close();
        return 1;
    }

    dataFile.close();

    // std::string dataFileName;

    // getline(std::cin, dataFileName);

    std::vector<ikeaData> warehouse;
    std::vector<ikeaData> shipmentData;
    readCSVFile(warehouse, shipmentData, configData["data_file"]);

    // inboundSort(warehouse, "price");

    unsigned int printStop = 10;
    std::cout << std::endl << "ShipmentData (size: " << shipmentData.size() << "):" << std::endl;
    if (shipmentData.size() < 1) { std::cout << "NO ITEMS IN SHIPMENTDATA!!" << std::endl; }
    else {
    for (unsigned int i = 0; i < printStop; ++i) {
        std::cout << shipmentData.at(i).id << ",{"
              << shipmentData.at(i).name << "},["
              << shipmentData.at(i).type << "],"
              << shipmentData.at(i).price << " >"
              << std::endl;
    }
    }


    std::cout << std::endl << "Warehouse (size: " << warehouse.size() << "):" << std::endl;
    if (warehouse.size() < 1) { std::cout << "NO ITEMS IN WAREHOUSE!!" << std::endl; }
    else {
    for (unsigned int i = 0; i < printStop; ++i) {
        std::cout << warehouse.at(i).id << ",{"
              << warehouse.at(i).name << "},["
              << warehouse.at(i).type << "],"
              << warehouse.at(i).price << " >"
              << std::endl;
    }
    }

    return 0;
}