#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ikea_data_struct.cpp"

double parseNumData(std::string& s) {
    try {
        short fIndex = s.find(',');
        std::string s2 = s.substr(0, fIndex);
        s = s.substr(fIndex + 1);
        return (std::stod(s2));
    } catch (std::invalid_argument e) {
        e.what();
    }

    return -1.0;
}

std::string parseStrData(std::string& s) {
    try {
        short fIndex = s.find(',');
        if (s.find("\"") == 0) { fIndex = s.find('\"', 1) + 1; }
        std::string s2 = s.substr(0, fIndex);
        if (s.size() > fIndex + 1) {
            s = s.substr(fIndex + 1);
        } else {
            s = "";
        }
        return s2;
    } catch (std::runtime_error e) {
        e.what();
    }

    return "error";
}

int main() {
    std::string dataFileName;

    getline(std::cin, dataFileName);

    std::ifstream dataFile(dataFileName);

    // Getting the header separately
    std::string dataHeader;
    std::getline(dataFile, dataHeader);

    ikeaData warehouse;

    int dataLength = 0;
    int STOPNUM = 3;
    std::string dataLine;
    while(std::getline(dataFile, dataLine) && dataLength != STOPNUM) {

        warehouse.id.push_back(parseNumData(dataLine));
        if (warehouse.id.at(warehouse.id.size() - 1) == -1) {
            warehouse.id.pop_back();
        }
        
        warehouse.name.push_back(parseStrData(dataLine));
        if (warehouse.name.at(warehouse.name.size() - 1) == "error") {
            warehouse.name.pop_back();
        }

        warehouse.type.push_back(parseStrData(dataLine));
        if (warehouse.type.at(warehouse.type.size() - 1) == "error") {
            warehouse.type.pop_back();
        }

        warehouse.price.push_back(parseNumData(dataLine));
        if (warehouse.price.at(warehouse.price.size() - 1) <= -0.9 
        || warehouse.price.at(warehouse.price.size() - 1) >= -1.1) {
            warehouse.price.pop_back();
        }
        
        dataLength++;
    }

    std::cout << warehouse.id.at(0) << ",{"
              << warehouse.name.at(0) << "},["
              << warehouse.type.at(0) << "],"
              << warehouse.price.at(0) << " >"
              << dataLength << std::endl;

    dataFile.close();

    return 0;
}