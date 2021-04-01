#pragma once
#include "BWAPI.h"

namespace BuildConditionEnums {
	enum class ConditionType {
		RESOURCE,
		UNIT,
		TECH,
		UPGRADE,
		NONE
	};

	enum class ResourceType {
		MINERAL,
		GAS,
		SUPPLY
	};
};

class BuildCondition {
public:
	BuildCondition();
	BuildCondition(BuildConditionEnums::ResourceType newResourceType, int value);
	BuildCondition(const BWAPI::UnitType *newUnitType, int value, bool unitCompleted = false);
	BuildCondition(const BWAPI::TechType *newTechType);
	BuildCondition(const BWAPI::UpgradeType *newUpgradeType, int value = 1);

	bool IsConditionMet() const;

private:
	BuildConditionEnums::ConditionType type_;
	BuildConditionEnums::ResourceType resourceType_;
	const BWAPI::UnitType *unitType_;
	const BWAPI::TechType *techType_;
	const BWAPI::UpgradeType *upgradeType_;
	int value_;
	bool unitCompleted_;

	bool IsResourceConditionMet() const;
	bool IsUnitConditionMet() const;
	bool IsTechConditionMet() const;
	bool IsUpgradeConditionMet() const;
};
