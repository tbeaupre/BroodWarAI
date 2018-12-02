#include "BuildAction.h"

using namespace BuildActionEnums;

BuildAction::BuildAction(const BWAPI::UnitType *unitType) {
	type_ = ActionType::UNIT;
	unitType_ = unitType;
}

BuildAction::BuildAction(const BWAPI::TechType *techType) {
	type_ = ActionType::TECH;
	techType_ = techType;
}

BuildAction::BuildAction(const BWAPI::UpgradeType *upgradeType) {
	type_ = ActionType::UPGRADE;
	upgradeType_ = upgradeType;
}

const std::string BuildAction::PrintAction() const {
	switch (type_) {
		case ActionType::UNIT:
			return unitType_->toString();
		case ActionType::TECH:
			return techType_->toString();
		case ActionType::UPGRADE:
			return upgradeType_->toString();
		default:
			return "";
	}
}
