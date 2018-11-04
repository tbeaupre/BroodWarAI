#pragma once
#include "BWAPI.h"

namespace BuildConditionEnums {
	enum ConditionType {
		RESOURCE,
		UNIT,
		TECH,
		UPGRADE,
		NONE
	};

	enum ResourceType {
		MINERAL,
		GAS,
		SUPPLY
	};
};

using namespace BuildConditionEnums;

class BuildCondition {
public:
	BuildCondition();
	BuildCondition(ResourceType newResourceType, int value);
	BuildCondition(const BWAPI::UnitType *newUnitType, int value);
	BuildCondition(const BWAPI::TechType *newTechType);
	BuildCondition(const BWAPI::UpgradeType *newUpgradeType, int value);

	bool IsConditionMet() const;

private:
	ConditionType type_;
	ResourceType resourceType_;
	const BWAPI::UnitType *unitType_;
	const BWAPI::TechType *techType_;
	const BWAPI::UpgradeType *upgradeType_;
	int value_;

	bool IsResourceConditionMet() const;
	bool IsUnitConditionMet() const;
	bool IsTechConditionMet() const;
	bool IsUpgradeConditionMet() const;
};
