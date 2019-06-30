#pragma once
#include "BuildOrderStep.h"

typedef std::vector<BuildOrderStep*> BuildOrder;

class BuildOrders {
public:
	static BuildOrder GetTest();
	static BuildOrder GetOverPool();
	static BuildOrder Get3BaseSpire5HatchHydra();
};