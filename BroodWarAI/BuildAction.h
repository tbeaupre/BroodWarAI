#pragma once
#include "BWAPI.h"

namespace BuildActionEnums {
	enum class ActionType {
		UNIT,
		UPGRADE,
		TECH,
		OTHER,
	};

	enum class OtherActionType {
		EXPAND,
	};

	enum class PriorityLevel {
		BUILD
	};
}

using namespace BuildActionEnums;

class BuildAction {
public:
	BuildAction(const BWAPI::UnitType *unitType, PriorityLevel priorityLevel = PriorityLevel::BUILD);
	BuildAction(const BWAPI::TechType *techType, PriorityLevel priorityLevel = PriorityLevel::BUILD);
	BuildAction(const BWAPI::UpgradeType *upgradeType, PriorityLevel priorityLevel = PriorityLevel::BUILD);
	BuildAction(BuildActionEnums::OtherActionType otherType, PriorityLevel priorityLevel = PriorityLevel::BUILD);

	ActionType getType() const { return type_; }
	const BWAPI::UnitType *getUnitType() const { return unitType_; }
	const BWAPI::TechType *getTechType() const { return techType_; }
	const BWAPI::UpgradeType *getUpgradeType() const { return upgradeType_; }
	OtherActionType getOtherType() const { return otherType_; }
	PriorityLevel getPriorityLevel() const { return priorityLevel_;  }

	bool isUnit() const { return type_ == ActionType::UNIT; }
	bool isBuilding() const { return type_ == ActionType::UNIT && unitType_->isBuilding(); }
	bool isTech() const { return type_ == ActionType::TECH; }
	bool isUpgrade() const { return type_ == ActionType::UPGRADE; }
	bool isOther() const { return type_ == ActionType::OTHER; }

	const std::string PrintAction() const;

private:
	BuildActionEnums::ActionType type_;
	const BWAPI::UnitType *unitType_;
	const BWAPI::TechType *techType_;
	const BWAPI::UpgradeType *upgradeType_;
	OtherActionType otherType_;
	PriorityLevel priorityLevel_;
};
