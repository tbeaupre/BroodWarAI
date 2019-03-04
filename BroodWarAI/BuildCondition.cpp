#include "BuildCondition.h"

using namespace BuildConditionEnums;

BuildCondition::BuildCondition() {
	type_ = ConditionType::NONE;
}

BuildCondition::BuildCondition(ResourceType resourceType, int value) {
	type_ = ConditionType::RESOURCE;
	resourceType_ = resourceType;
	value_ = value;
}

BuildCondition::BuildCondition(const BWAPI::UnitType *unitType, int value, bool unitCompleted) {
	type_ = ConditionType::UNIT;
	unitType_ = unitType;
	value_ = value;
	unitCompleted_ = unitCompleted;
}

BuildCondition::BuildCondition(const BWAPI::TechType *techType) {
	type_ = ConditionType::TECH;
	techType_ = techType;
}

BuildCondition::BuildCondition(const BWAPI::UpgradeType *upgradeType, int value) {
	type_ = ConditionType::UPGRADE;
	upgradeType_ = upgradeType;
	value_ = value;
}

bool BuildCondition::IsConditionMet() const {
	switch (type_) {
		case ConditionType::NONE:
			return true;
		case ConditionType::RESOURCE:
			return IsResourceConditionMet();
		case ConditionType::UNIT:
			return IsUnitConditionMet();
		case ConditionType::TECH:
			return IsTechConditionMet();
		case ConditionType::UPGRADE:
			return IsUpgradeConditionMet();
		default:
			return true;
	}
}

bool BuildCondition::IsResourceConditionMet() const {
	switch (resourceType_) {
		case ResourceType::SUPPLY:
			return BWAPI::Broodwar->self()->supplyUsed() == value_;
		case ResourceType::MINERAL:
			return BWAPI::Broodwar->self()->minerals() >= value_;
		case ResourceType::GAS:
			return BWAPI::Broodwar->self()->gas() >= value_;
		default:
			return true;
	}
}

bool BuildCondition::IsUnitConditionMet() const {
	BWAPI::Unitset units = BWAPI::Broodwar->self()->getUnits();
	int count = 0;
	for (auto u = units.begin(); u != units.end(); ++u) {
		BWAPI::Unit unit = *u;
		if (unit->exists() &&
			unit->getType() == *unitType_) {
			if (unit->isCompleted() || (!unitCompleted_ && unit->isBeingConstructed())) {
				++count;
			}
		}
	}
	return count >= value_;
}

bool BuildCondition::IsTechConditionMet() const {
	return BWAPI::Broodwar->self()->hasResearched(*techType_);
}

bool BuildCondition::IsUpgradeConditionMet() const {
	return BWAPI::Broodwar->self()->getUpgradeLevel(*upgradeType_) == value_;
}
