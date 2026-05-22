#include "ikea_data_struct.h"
#include <random>
#include <vector>

void inboundShippment(std::vector<ikeaData>& wh, std::vector<ikeaData>& shipments, int amount);
void outboundShippment(std::vector<ikeaData>& wh, int amount);

void startSim(std::vector<ikeaData>& wh, int minInb, int maxInb, int minOutb, int maxOutb,
              int minInbFeq, int maxInbFeq, int minOutbFeq, int maxOutbFeq);