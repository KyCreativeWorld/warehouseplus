#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <thread>
#include "backend/nlohmann/json.hpp"
#include "backend/ikea_data_struct.h"
#include "backend/inbound_sort.h"
#include "backend/read_csv_file.cpp"

using json = nlohmann::json;

int main() {
    auto clockStart = std::chrono::high_resolution_clock::now();

    std::ifstream dataFile("backend/config.json");

    json configData;
    try {
        dataFile >> configData;
    } catch (const json::parse_error& e) {
        std::cout << "JSON Parsing Error: " << e.what() << std::endl;
        return 1;
    }

    dataFile.close();

    std::vector<ikeaData> warehouse;
    std::vector<ikeaData> shipmentData;

    std::string whFileName = configData["data_file"];
    whFileName.erase(remove(whFileName.begin(), whFileName.end(), '\"'), whFileName.end());
    std::cout << "data_file: " << whFileName << std::endl;
    readCSVFile(warehouse, shipmentData, whFileName);

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



    bool programRunning = true;
    std::ofstream warehouseInfoFile("../warehouseplus_gui/warehouse_info.json");
    std::ofstream newDataAvailableNotificationFile("../warehouseplus_gui/new_data_available.txt");

    while (programRunning) {
        
        if (!warehouseInfoFile.is_open()) {
            std::cerr << "[ERROR] Could not write to file!" << std::endl;
        } else {
            warehouseInfoFile << "{\"warehouse_size\": " << warehouse.size() << "}";
        }
       
        simInfoFile.close();
        newDataAvailableNotificationFile.close();

        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        if (!std::filesystem::exists("backend/simulator_info.json")) programRunning = false;
    }

    warehouseInfoFile.close();

    try {
        // std::filesystem::remove returns true if the file was deleted, false if it didn't exist
        if (std::filesystem::remove("../warehouseplus_gui/warehouse_info.json")) {
            std::cout << "Cleanup successful: warehouse_info.json file deleted.\n";
        } else {
            std::cout << "Cleanup note: File did not exist.\n";
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Cleanup Error: Could not delete file. " << e.what() << '\n';
    }

    return 0;
}