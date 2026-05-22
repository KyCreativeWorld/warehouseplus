#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "ikea_data_struct.h"

void bulkSort(std::vector<ikeaData>& wh, std::string sortBy = "id", size_t stopNum = 0);

void applyPermutation(std::vector<ikeaData>& wh, std::vector<size_t>& indices);