#include "BWAPI.h"
#include "BuildOrders.h"

BuildOrder BuildOrders::GetOverPool() {
	BuildOrder result = {
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Drone),
			5),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Overlord)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Spawning_Pool)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Drone),
			2),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Spawning_Pool, 1),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Zergling),
			3),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Hatchery),
			2)
	};

	return result;
}
