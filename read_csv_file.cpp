#include "read_csv_file.h"

double parseNumData(std::string& s) {
    try {
        short fIndex = s.find(',');
        std::string_view s2 = s;
        s2 = s2.substr(0, fIndex);
        s = s.substr(fIndex + 1);
        return -1.0;
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

void readCSVFile(ikeaData& warehouse, std::string fn) {
    std::ifstream dataFile(fn);

    // Getting the header separately
    std::string dataHeader;
    std::getline(dataFile, dataHeader);

    ikeaData warehouse;

    int dataLength = 0;
    int STOPNUM = 10;
    std::string dataLine;
    while(std::getline(dataFile, dataLine) && dataLength != STOPNUM) {

        warehouse.id.push_back(parseNumData(dataLine));
        if (warehouse.id.at(warehouse.id.size() - 1) == -1) {
            warehouse.id.pop_back();
            continue;
        }
        
        warehouse.name.push_back(parseStrData(dataLine));
        if (warehouse.name.at(warehouse.name.size() - 1) == "error") {
            warehouse.id.pop_back();
            warehouse.name.pop_back();
            continue;
        }

        warehouse.type.push_back(parseStrData(dataLine));
        if (warehouse.type.at(warehouse.type.size() - 1) == "error") {
            warehouse.id.pop_back();
            warehouse.name.pop_back();
            warehouse.type.pop_back();
            continue;
        }

        warehouse.price.push_back(parseNumData(dataLine));
        if (warehouse.price.at(warehouse.price.size() - 1) <= -0.9 
        && warehouse.price.at(warehouse.price.size() - 1) >= -1.1) {
            warehouse.id.pop_back();
            warehouse.name.pop_back();
            warehouse.type.pop_back();
            warehouse.price.pop_back();
            continue;
        }
        
        dataLength++;
    }

    dataFile.close();
}