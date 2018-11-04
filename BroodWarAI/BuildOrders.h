#pragma once
#include "BuildOrderStep.h"

typedef std::vector<BuildOrderStep*> BuildOrder;

static class BuildOrders {
public:
	std::vector<BuildOrderStep*> getOverPool();

};