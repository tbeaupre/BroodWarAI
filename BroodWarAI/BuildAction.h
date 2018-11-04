#pragma once
#include "BWAPI.h"

enum BuildActionType {
	Unit,
	Upgrade,
	Tech,
};

class BuildAction {
public:
	BuildAction(const BWAPI::UnitType *newUnit);
	BuildAction(const BWAPI::TechType *newTech);
	BuildAction(const BWAPI::UpgradeType *newUpgrade);

	const BuildActionType getType();
	const BWAPI::UnitType *getUnitType();
	const BWAPI::TechType *getTechType();
	const BWAPI::UpgradeType *getUpgradeType();

	bool isUnit();
	bool isBuilding();
	bool isTech();
	bool isUpgrade();

private:
	BuildActionType type;
	const BWAPI::UnitType *unitType;
	const BWAPI::TechType *techType;
	const BWAPI::UpgradeType *upgradeType;
};
