#include "Nolsy.h"
#include "UnitManager.h"
#include "BaseManager.h"

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
			break;
		case UNSTARTED:
			HandleAction();
			break;
	}
}

void Nolsy::Create() {
	UnitManager::RegisterForUnitComplete(this, unit_->getType());
	status_ = CANCELLABLE;
}

void Nolsy::Complete() {
	Suicide();
}

void Nolsy::Destroy() {
	unit_ = nullptr;
	status_ = UNSTARTED;
}

void Nolsy::SoftCancel() {
	// TODO: Decide what to do about unregistering from UnitManager. Might make more sense to just have hard cancel for v1.
	Cancel();
	status_ = PAUSED;
}

void Nolsy::Resume() {
	status_ = UNSTARTED;
}

void Nolsy::HardCancel() {
	Cancel();
	Suicide();
}

void Nolsy::Cancel() {
	if (!unit_) {
		return; // If the build hasn't started, don't worry about cancelling it.
	}
	switch (action_->getType()) {
		case ActionType::UNIT:
			if (unit_->isBeingConstructed()) {
				unit_->cancelConstruction();
				break;
			}
			unit_->cancelMorph();
			break;
		case ActionType::TECH:
			unit_->cancelResearch();
			break;
		case ActionType::UPGRADE:
			unit_->cancelUpgrade();
			break;
		case ActionType::OTHER:
			// TODO: yeah, this need to get some love.
			break;
	}
}

void Nolsy::Suicide() {
	// Tell the boys back home the job's done.
}

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
					unit_ = larva;
					UnitManager::RegisterForUnitComplete(this, *unitType);
					status_ = CANCELLABLE;
				};
			}
			break;
	}
}

void Nolsy::HandleStructureAction(const UnitType *unitType) {
	switch (*unitType) {
		case UnitTypes::Zerg_Greater_Spire:
		case UnitTypes::Zerg_Lair:
		case UnitTypes::Zerg_Hive:
			unit_ = UnitManager::ReserveStructure(unitType->whatBuilds().first);
			if (unit_ && unit_->exists()) {
				if (unit_->build(*unitType)) {
					UnitManager::RegisterForUnitComplete(this, *unitType);
					status_ = CANCELLABLE;
				}
			}
			return;
		case UnitTypes::Zerg_Extractor:
			// This should probably be put under the Other action.
			return;
		case UnitTypes::Zerg_Creep_Colony:
			// This should probably be put under the Other action.
			return;
	}

	if (!unit_) {
		// Need to get a worker.
		unit_ = UnitManager::ReserveWorker();
		if (!unit_ || !unit_->exists()) {
			unit_ = nullptr;
			return; // No worker. So... gtfo of my room, I'm playing Minecraft!
		}
	}

	if (!targetLocation_) {
		// Need to figure out where to build.
		targetLocation_ = &Broodwar->getBuildLocation(*unitType, unit_->getTilePosition());
		if (*targetLocation_ == TilePositions::Invalid) {
			targetLocation_ = nullptr;
			return; // Failed to find a place to build.
		}
	}

	if (unit_->build(*unitType, *targetLocation_)) {
		UnitManager::RegisterForUnitCreate(this, *unitType);
		UnitManager::RegisterForUnitDestroy(this, unit_->getType());
		status_ = STOPPABLE;
	}
}

void Nolsy::HandleTechAction(const TechType *techType) {
	if (BWAPI::Broodwar->self()->isResearching(*techType)) {
		Broodwar << "Tech successfully started." << std::endl;
		status_ = CANCELLABLE;
		return;
	}

	if (!unit_) {
		unit_ = UnitManager::ReserveStructure(techType->whatResearches());
	}

	if (unit_ && unit_->exists()) {
		unit_->research(*techType);
	}
}

void Nolsy::HandleUpgradeAction(const UpgradeType *upgradeType) {
	if (BWAPI::Broodwar->self()->isUpgrading(*upgradeType)) {
		Broodwar << "Upgrade successfully started." << std::endl;
		status_ = CANCELLABLE;
		return;
	}

	if (!unit_) {
		unit_ = UnitManager::ReserveStructure(upgradeType->whatUpgrades());
	}

	if (unit_ && unit_->exists()) {
		unit_->upgrade(*upgradeType);
	}
}

void Nolsy::HandleOtherAction(const BuildActionEnums::OtherActionType otherType) {}
