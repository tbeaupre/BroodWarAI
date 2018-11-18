#include "Nolsy.h"
#include "UnitManager.h"

using namespace BWAPI;
using namespace BuildActionEnums;

Nolsy::Nolsy(const BuildAction *action) {
	action_ = action;
}

void Nolsy::Update() {
	switch (status_) {
		case PAUSED:
			break;
		case CANCELLABLE:
			break;
		case STOPPABLE:
			HandleAction();
			break;
	}
}

void Nolsy::SoftCancel() {
	Cancel();
	status_ = PAUSED;
}

void Nolsy::Resume() {
	// TODO: Handle restarting build operations/disappearing drones.
	status_ = STOPPABLE;
}

void Nolsy::HardCancel() {
	Cancel();
	Suicide();
}

void Nolsy::Cancel() {
	if (!target_) {
		return; // If the build hasn't started, don't worry about cancelling it.
	}
	switch (action_->getType()) {
		case ActionType::UNIT:
			if (target_->isBeingConstructed()) {
				target_->cancelConstruction();
				break;
			}
			target_->cancelMorph();
			break;
		case ActionType::TECH:
			target_->cancelResearch();
			break;
		case ActionType::UPGRADE:
			target_->cancelUpgrade();
			break;
		case ActionType::OTHER:
			// TODO: yeah, this need to get some love.
			break;
	}
}

void Nolsy::Suicide() {}

void Nolsy::HandleAction() {
	switch (action_->getType()) {
		case ActionType::UNIT:
			if (action_->isBuilding()) {
				HandleStructureAction(action_->getUnitType());
				break;
			}
			HandleUnitAction(action_->getUnitType());
			break;
		case ActionType::TECH:
			HandleTechAction(action_->getTechType());
			break;
		case ActionType::UPGRADE:
			HandleUpgradeAction(action_->getUpgradeType());
			break;
		case ActionType::OTHER:
			HandleOtherAction(action_->getOtherType());
			break;
	}
}

void Nolsy::HandleUnitAction(const UnitType *unitType) {
	switch (*unitType) {
		case UnitTypes::Zerg_Lurker:
			// This is where you turn a Hydra into a Lurker. I swear I had something for this.
			break;
		default:
			Unit larva = UnitManager::GetLarva();
			if (larva && larva->exists()) {
				if (larva->morph(*unitType)) {
					target_ = larva;
					Broodwar << "Unit morph successfully started." << std::endl;
					status_ = CANCELLABLE;
				};
			}
			break;
	}
}

void Nolsy::HandleStructureAction(const UnitType *unitType) {}

void Nolsy::HandleTechAction(const TechType *techType) {
	if (BWAPI::Broodwar->self()->isResearching(*techType)) {
		Broodwar << "Tech successfully started." << std::endl;
		status_ = CANCELLABLE;
		return;
	}

	if (!target_) {
		target_ = UnitManager::ReserveStructure(techType->whatResearches());
	}

	if (target_ && target_->exists()) {
		target_->research(*techType);
	}
}

void Nolsy::HandleUpgradeAction(const UpgradeType *upgradeType) {
	if (BWAPI::Broodwar->self()->isUpgrading(*upgradeType)) {
		Broodwar << "Upgrade successfully started." << std::endl;
		status_ = CANCELLABLE;
		return;
	}

	if (!target_) {
		target_ = UnitManager::ReserveStructure(upgradeType->whatUpgrades());
	}

	if (target_ && target_->exists()) {
		target_->upgrade(*upgradeType);
	}
}

void Nolsy::HandleOtherAction(const BuildActionEnums::OtherActionType otherType) {}
