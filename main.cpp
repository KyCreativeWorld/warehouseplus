#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "ikea_data_struct.h"
#include "insertion_sort_warehouse.h"
#include "read_csv_file.h"

int main() {
    std::string dataFileName;

    getline(std::cin, dataFileName);

    ikeaData warehouse;
    readCSVFile(warehouse, dataFileName);

    insertionSort(warehouse, "price");

    unsigned int printStop = 10;
    for (unsigned int i = 0; i < printStop; ++i) {
        std::cout << warehouse.id.at(i) << ",{"
              << warehouse.name.at(i) << "},["
              << warehouse.type.at(i) << "],"
              << warehouse.price.at(i) << " >"
              << std::endl;
    }

    return 0;
}