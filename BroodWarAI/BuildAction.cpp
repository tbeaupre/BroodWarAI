#include "BuildAction.h"

BuildAction::BuildAction(const BWAPI::UnitType *newUnit) {
	type = BuildActionType::Unit;
	unitType = newUnit;
}

BuildAction::BuildAction(const BWAPI::TechType *newTech) {
	type = BuildActionType::Tech;
	techType = newTech;
}

BuildAction::BuildAction(const BWAPI::UpgradeType *newUpgrade) {
	type = BuildActionType::Upgrade;
	upgradeType = newUpgrade;
}

const BuildActionType BuildAction::getType() {
	return type;
}

const BWAPI::UnitType *BuildAction::getUnitType() {
	return unitType;
}

const BWAPI::TechType *BuildAction::getTechType() {
	return techType;
}

const BWAPI::UpgradeType *BuildAction::getUpgradeType() {
	return upgradeType;
}

bool BuildAction::isUnit() {
	return type == BuildActionType::Unit;
}

bool BuildAction::isBuilding() {
	return type == BuildActionType::Unit && unitType->isBuilding();
}

bool BuildAction::isTech() {
	return type == BuildActionType::Tech;
}

bool BuildAction::isUpgrade() {
	return type == BuildActionType::Upgrade;
}