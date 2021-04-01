#include "BuildAction.h"

using namespace BuildActionEnums;

BuildAction::BuildAction(const BWAPI::UnitType *unitType, PriorityLevel priorityLevel) {
	type_ = ActionType::UNIT;
	unitType_ = unitType;
	priorityLevel_ = priorityLevel;
}

BuildAction::BuildAction(const BWAPI::TechType *techType, PriorityLevel priorityLevel) {
	type_ = ActionType::TECH;
	techType_ = techType;
	priorityLevel_ = priorityLevel;
}

BuildAction::BuildAction(const BWAPI::UpgradeType *upgradeType, PriorityLevel priorityLevel) {
	type_ = ActionType::UPGRADE;
	upgradeType_ = upgradeType;
	priorityLevel_ = priorityLevel;
}

BuildAction::BuildAction(BuildActionEnums::OtherActionType otherType, PriorityLevel priorityLevel) {
	type_ = ActionType::OTHER;
	otherType_ = otherType;
	priorityLevel_ = priorityLevel;
}

const std::string BuildAction::PrintAction() const {
	switch (type_) {
		case ActionType::UNIT:
			return unitType_->toString();
		case ActionType::TECH:
			return techType_->toString();
		case ActionType::UPGRADE:
			return upgradeType_->toString();
		case ActionType::OTHER:
			return "Expanding";
		default:
			return "";
	}
}
