#pragma once
#include "BuildOrderStep.h"

typedef std::vector<BuildOrderStep*> BuildOrder;

class BuildOrders {
public:
	static BuildOrder GetOverPool();
};