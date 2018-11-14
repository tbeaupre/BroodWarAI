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

void BuildAction::PrintAction() const {
	switch (type_) {
		case ActionType::UNIT:
			BWAPI::Broodwar << unitType_->toString() << std::endl;
			break;
		case ActionType::TECH:
			BWAPI::Broodwar << techType_->toString() << std::endl;
			break;
		case ActionType::UPGRADE:
			BWAPI::Broodwar << upgradeType_->toString() << std::endl;
			break;
		default:
			BWAPI::Broodwar << std::endl;
			break;
	}
}
