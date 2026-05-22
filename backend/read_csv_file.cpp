#include "read_csv_file.h"

double parseNumData(std::string& s) {
    size_t commaPos = s.find(',');
    std::string valStr = s.substr(0, commaPos);
    
    // Update the original string to remove the part we just read
    if (commaPos != std::string::npos) {
        s = s.substr(commaPos + 1);
    } else {
        s = "";
    }

    try {
        // Use std::stod for the actual conversion
        return std::stod(valStr);
    } catch (...) {
        return -1.0; // Return error code only if parsing fails
    }
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

bool addData(std::vector<ikeaData>& warehouse, std::string dataLine) {
    ikeaData tempD;
    
    tempD.id = parseNumData(dataLine);
    if (tempD.id == -1) {
        return false;
    }
    
    tempD.name = parseStrData(dataLine);
    if (tempD.name == "error") {
        return false;
    }

    tempD.type = parseStrData(dataLine);
    if (tempD.type == "error") {
        return false;
    }

    tempD.price = parseNumData(dataLine);
    if (tempD.price <= -0.9 && tempD.price >= -1.1) {
        return false;
    }

    warehouse.push_back(tempD);
    return true;
}



void readCSVFile(std::vector<ikeaData>& warehouse, std::vector<ikeaData>& shipmentData, std::string fn) {
    std::ifstream dataFile(fn);

    // Getting the header separately
    std::string dataHeader;
    std::getline(dataFile, dataHeader);

    int dataLength = 0;
    size_t STOPNUM = 500000;

    bool addDataSuccess;
    std::string dataLine;
    while(std::getline(dataFile, dataLine) && dataLength != STOPNUM) {   
        if (dataLength < 300) { 
            addDataSuccess = addData(shipmentData, dataLine);
        } else {
            addDataSuccess = addData(warehouse, dataLine);
        }
        
        if (addDataSuccess) dataLength++;
    }

    dataFile.close();
}