#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ikea_item_struct.cpp"

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

    std::vector<ikeaItem> warehouse;
    warehouse.reserve(1000);

    int dataLength = 0;
    int numTries = 0;
    int STOPNUM = 3;
    std::string dataLine;
    while(std::getline(dataFile, dataLine) && dataLength != STOPNUM) {
        ikeaItem tempItem;
        numTries++;

        tempItem.id = parseNumData(dataLine);
        if (tempItem.id == -1) continue;

        tempItem.name = parseStrData(dataLine);
        if (tempItem.name == "error") continue;

        tempItem.type = parseStrData(dataLine);
        if (tempItem.type == "error") continue;

        tempItem.price = parseNumData(dataLine);
        if (tempItem.price == -1.0) continue;
        
        dataLength++;
        warehouse.push_back(tempItem);
    }

    std::cout << warehouse.at(0).id << ",{"
              << warehouse.at(0).name << "},["
              << warehouse.at(0).type << "],"
              << warehouse.at(0).price << " >"
              << numTries << std::endl;

    dataFile.close();

    return 0;
}