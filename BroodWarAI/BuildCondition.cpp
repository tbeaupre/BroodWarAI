#include "BuildCondition.h"

BuildCondition::BuildCondition() {
	type = BuildConditionType::None;
}

BuildCondition::BuildCondition(BuildConditionResource newResourceType, int resourceValue) {
	type = BuildConditionType::Resource;
	resourceType = newResourceType;
	value = resourceValue;
}

BuildCondition::BuildCondition(const BWAPI::UnitType *newUnitType, int unitValue) {
	type = BuildConditionType::Unit;
	unitType = newUnitType;
	value = unitValue;
}

BuildCondition::BuildCondition(const BWAPI::TechType *newTechType) {
	type = BuildConditionType::Tech;
	techType = newTechType;
}

BuildCondition::BuildCondition(const BWAPI::UpgradeType *newUpgradeType, int upgradeValue) {
	type = BuildConditionType::Upgrade;
	upgradeType = newUpgradeType;
	value = upgradeValue;
}

bool BuildCondition::isConditionMet() {
	switch (type) {
		case BuildConditionType::None:
			return true;
		case BuildConditionType::Resource:
			return isResourceConditionMet();
		case BuildConditionType::Unit:
			return isUnitConditionMet();
		case BuildConditionType::Tech:
			return isTechConditionMet();
		case BuildConditionType::Upgrade:
			return isUpgradeConditionMet();
		default:
			return true;
	}
}

bool BuildCondition::isResourceConditionMet() {
	switch (resourceType) {
		case BuildConditionResource::Supply:
			return BWAPI::Broodwar->self()->supplyUsed() == value;
		case BuildConditionResource::Mineral:
			return BWAPI::Broodwar->self()->minerals() >= value;
		case BuildConditionResource::Gas:
			return BWAPI::Broodwar->self()->gas() >= value;
		default:
			return true;
	}
}

bool BuildCondition::isUnitConditionMet() {
	BWAPI::Unitset units = BWAPI::Broodwar->self()->getUnits();
	int count = 0;
	for (auto u = units.begin(); u != units.end(); ++u) {
		BWAPI::Unit unit = *u;
		if (unit->exists() &&
			unit->isCompleted &&
			unit->getType() == *unitType) {
			++count;
		}
	}
	return count >= value;
}

bool BuildCondition::isTechConditionMet() {
	return BWAPI::Broodwar->self()->hasResearched(*techType);
}

bool BuildCondition::isUpgradeConditionMet() {
	return BWAPI::Broodwar->self()->getUpgradeLevel(*upgradeType) == value;
}
