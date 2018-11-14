#pragma once
#include "BWAPI.h"

namespace BuildActionEnums {
	enum ActionType {
		UNIT,
		UPGRADE,
		TECH,
	};
}

class BuildAction {
public:
	BuildAction(const BWAPI::UnitType *unitType);
	BuildAction(const BWAPI::TechType *techType);
	BuildAction(const BWAPI::UpgradeType *upgradeType);

	BuildActionEnums::ActionType getType() const { return type_; }
	const BWAPI::UnitType *getUnitType() const { return unitType_; }
	const BWAPI::TechType *getTechType() const { return techType_; }
	const BWAPI::UpgradeType *getUpgradeType() const { return upgradeType_; }

	bool isUnit() const { return type_ == ActionType::UNIT; }
	bool isBuilding() const { return type_ == ActionType::UNIT && unitType_->isBuilding(); }
	bool isTech() const { return type_ == ActionType::TECH; }
	bool isUpgrade() const { return type_ == ActionType::UPGRADE; }

	void PrintAction() const;

private:
	BuildActionEnums::ActionType type_;
	const BWAPI::UnitType *unitType_;
	const BWAPI::TechType *techType_;
	const BWAPI::UpgradeType *upgradeType_;
};
