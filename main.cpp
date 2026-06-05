#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <thread>
//#include <algorithm>
#include "backend/nlohmann/json.hpp"
#include "backend/ikea_data_struct.h"
#include "backend/read_csv_file.h"
#include "backend/inb_outb_sim.h"
#include "backend/bulk_sort.h"

using json = nlohmann::json;

int main() {

    std::ifstream dataFile("backend/config.json");

    json configData;
    std::string whFileName = "IKEA_warehouse_data.csv";
    try {
        dataFile >> configData;
        whFileName = configData["data_file"].get<std::string>();
    } catch (const json::parse_error& e) {
        std::cout << "JSON Parsing Error: " << e.what() << std::endl;
        return 1;
    }

    dataFile.close();

    std::vector<ikeaData> warehouse;
    std::vector<ikeaData> shipmentData;

    whFileName.erase(remove(whFileName.begin(), whFileName.end(), '\"'), whFileName.end());
    std::cout << "data_file: " << whFileName << std::endl;

    //Choose n for runtime, used for timing code
    size_t n = 1000;

    auto clockStart = std::chrono::high_resolution_clock::now();                        //TIMER IS HERE
// Code you want to measure
    readCSVFile(warehouse, shipmentData, whFileName, n);                    
    auto clockEnd = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        clockEnd - clockStart
    );
    std::cout << "Read at n = " << n << ": " << duration.count() << " milliseconds\n";


    clockStart = std::chrono::high_resolution_clock::now();                        //TIMER IS HERE
// Code you want to measure
    bulkSort(warehouse);
    clockEnd = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(
        clockEnd - clockStart
    );
    std::cout << "Bulksort at n = " << n << ": " << duration.count() << " milliseconds\n";


    unsigned int printStop = 100;
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



    RandomGenerator randGen;

    bool programRunning = true;

    unsigned int timer = 0;

    json simInfo;

    int delResult;
    int saleResult;
    while (programRunning) {

        clockStart = std::chrono::high_resolution_clock::now();                    //TIMER IS HERE
    // Code you want to measure
        delResult = deleteItemsUpdate(warehouse, 10);
        clockEnd = std::chrono::high_resolution_clock::now();

        if (delResult != -1) {
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                clockEnd - clockStart
            );
            std::cout << "Delete at n = " << n << ": " << duration.count() << " milliseconds\n";
        }        
        
        clockStart = std::chrono::high_resolution_clock::now();                    //TIMER IS HERE
    // Code you want to measure
        saleResult = putItemsOnSale(warehouse, 10);
        clockEnd = std::chrono::high_resolution_clock::now();

        if (saleResult != -1) {
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                clockEnd - clockStart
            );
            std::cout << "Update at n = " << n << ": " << duration.count() << " milliseconds\n";
        }
        
        

        if (timer > 0) timer--;
        
        std::ofstream newDataAvailableNotificationFile("../warehouseplus_gui/new_data_available.txt");
        std::ofstream warehouseInfoFile("../warehouseplus_gui/warehouse_info.json");
        
        if (!warehouseInfoFile.is_open()) {
            std::cerr << "[ERROR] Could not write to file!" << std::endl;
        } else {
            warehouseInfoFile << "{\"warehouse_size\": " << warehouse.size()
                              << ",\"inb_shipments\":" << numInboundShippments
                              << ",\"outb_shipments\":" << numOutboundShippments
                              << ",\"first_item_price\":" << warehouse.at(0).price << "}";
        }
       
        warehouseInfoFile.close();
        newDataAvailableNotificationFile.close();



        if (std::filesystem::exists("backend/simulator_info.json")) {
            try {
                std::ifstream simInfoFile("backend/simulator_info.json");
                
                simInfo << simInfoFile;
            } catch (const json::parse_error& e) {
                std::cout << "JSON Parsing Error for simInfoFile: " << e.what() << std::endl;
            }

            if (simInfo["sim_active"].get<bool>() && timer == (unsigned int)0) {
                timer = 10 * runShipments(warehouse, shipmentData, simInfo, randGen);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (!std::filesystem::exists("backend/is_running.txt")) programRunning = false;
    }

    try {
        // std::filesystem::remove returns true if the file was deleted, false if it didn't exist
        if (std::filesystem::remove("../warehouseplus_gui/warehouse_info.json")) {
            std::cout << "Cleanup successful: warehouse_info.json file deleted.\n";
        } else {
            std::cout << "Cleanup note: warehouse_info.json did not exist.\n";
        }

        if (std::filesystem::remove("../warehouseplus_gui/new_data_available.txt")) {
            std::cout << "Cleanup successful: new_data_available.txt file deleted.\n";
        } else {
            std::cout << "Cleanup note: new_data_available.txt did not exist.\n";
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Cleanup Error: Could not delete file. " << e.what() << '\n';
    }

    return 0;
}