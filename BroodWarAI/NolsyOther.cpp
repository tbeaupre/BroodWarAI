#include "NolsyOther.h"
#include "UnitManager.h"
#include "BaseManager.h"

using namespace BWAPI;
using namespace BuildActionEnums;

NolsyOther::NolsyOther(BuildActionEnums::OtherActionType otherType)
{
	Broodwar << "NolsyOther::NolsyOther: Creating Expansion Nolsy" << std::endl;
	otherType_ = otherType;
}

void NolsyOther::Complete() {
	BaseManager::TakeNextBase();
	NolsyBase::Complete();
}

void NolsyOther::Cancel()
{
	if (!unit_) {
		return;
	}
	unit_->cancelConstruction();
}

void NolsyOther::HandleUnstarted() {
	switch (otherType_) {
		case OtherActionType::EXPAND:
			break;
	}
	BWAPI::Broodwar->sendText("ATTEMPTING TO EXPAND");

	if (!unit_) {
		BWAPI::Broodwar->sendText("NO WORKER");
		// Need to get a worker.
		unit_ = UnitManager::ReserveWorker();
		if (!unit_ || !unit_->exists()) {
			unit_ = nullptr;
			BWAPI::Broodwar->sendText("COULD NOT FIND WORKER");
			return; // No worker. So... gtfo of my room, I'm playing Minecraft!
		}
	}

	if (!targetLocation_) {
		BWAPI::Broodwar->sendText("FINDING BASE");
		// Need to figure out where to build.
		targetLocation_ = BaseManager::GetNextBaseTilePosition();
	}

	// NEED TO EXPLORE LOCATION FIRST!
	if (targetLocation_ && unit_ && unit_->canMove() && unit_->move(BWAPI::Position(*targetLocation_))) {
		BWAPI::Broodwar->sendText("MOVING TO LOCATION");
		status_ = CANCELLABLE;
	}
}

void NolsyOther::HandleCancellable() {
	if (unit_->build(UnitTypes::Zerg_Hatchery, *targetLocation_)) {
		BWAPI::Broodwar->sendText("BUILDING EXPANSION");
		UnitManager::RegisterForUnitCreate(this, UnitTypes::Zerg_Hatchery);
		UnitManager::RegisterForUnitDestroy(this, unit_->getType());
		status_ = STOPPABLE;
	}
}