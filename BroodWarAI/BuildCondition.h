#pragma once
#include "BWAPI.h"

enum BuildConditionType {
	Resource,
	Unit,
	Tech,
	Upgrade,
	None
};

enum BuildConditionResource {
	Mineral,
	Gas,
	Supply
};

class BuildCondition {
public:
	BuildCondition();
	BuildCondition(BuildConditionResource newResourceType, int resourceValue);
	BuildCondition(const BWAPI::UnitType *newUnitType, int unitValue);
	BuildCondition(const BWAPI::TechType *newTechType);
	BuildCondition(const BWAPI::UpgradeType *newUpgradeType, int upgradeValue);

	bool isConditionMet();
	bool isResourceConditionMet();
	bool isUnitConditionMet();
	bool isTechConditionMet();
	bool isUpgradeConditionMet();

private:
	BuildConditionType type;
	BuildConditionResource resourceType;
	const BWAPI::UnitType *unitType;
	const BWAPI::TechType *techType;
	const BWAPI::UpgradeType *upgradeType;
	int value;
};
