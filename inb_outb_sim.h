#include "ikea_data_struct.h"
#include <random>

void inboundShippment(ikeaData& wh, int amount);
void outboundShippment(ikeaData& wh, int amount);

void startSim(ikeaData& wh, int minInb, int maxInb, int minOutb, int maxOutb,
              int minInbFeq, int maxInbFeq, int minOutbFeq, int maxOutbFeq);