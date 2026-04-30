#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <charconv>
#include "ikea_data_struct.h"

double parseNumData(std::string& s);

std::string parseStrData(std::string& s);

void readCSVFile(ikeaData& warehouse, std::string fn);