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

	bool isUnit() const;
	bool isBuilding() const;
	bool isTech() const;
	bool isUpgrade() const;
	void PrintAction() const;

private:
	BuildActionEnums::ActionType type_;
	const BWAPI::UnitType *unitType_;
	const BWAPI::TechType *techType_;
	const BWAPI::UpgradeType *upgradeType_;
};
