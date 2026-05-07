#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "ikea_data_struct.h"

void bulkSort(ikeaData& wh, std::string sortBy = "id", size_t stopNum = 0);