#include "NolsyOther.h"
#include "UnitManager.h"
#include "BaseManager.h"

using namespace BWAPI;
using namespace BuildActionEnums;

NolsyOther::NolsyOther(BuildActionEnums::OtherActionType otherType)
{
	otherType_ = otherType;
}

void NolsyOther::OnCompleteUnit() {
	BaseManager::TakeNextBase();
	NolsyBase::OnCompleteUnit();
}

void NolsyOther::HandleUnstarted() {
	switch (otherType_) {
		case OtherActionType::EXPAND:
			break;
	}

	if (!unit_) {
		// Need to get a worker.
		unit_ = UnitManager::ReserveWorker();
		if (!unit_ || !unit_->exists()) {
			unit_ = nullptr;
			BWAPI::Broodwar->sendText("COULD NOT FIND WORKER");
			return; // No worker. So... gtfo of my room, I'm playing Minecraft!
		}
	}

	if (!targetLocation_) {
		// Need to figure out where to build.
		targetLocation_ = BaseManager::GetNextBaseTilePosition();
	}

	// NEED TO EXPLORE LOCATION FIRST!
	if (targetLocation_ && unit_ && unit_->canMove() && unit_->move(BWAPI::Position(*targetLocation_))) {
		BWAPI::Broodwar->sendText("MOVING TO LOCATION");
		status_ = Status::STOPPABLE;
	}
}

void NolsyOther::HandleStoppable() {
	if (unit_->build(UnitTypes::Zerg_Hatchery, *targetLocation_)) {
		BWAPI::Broodwar->sendText("BUILDING EXPANSION");
		UnitManager::RegisterForUnitMorph(this, unit_);
		status_ = Status::CANCELLABLE;
	}
}

void NolsyOther::Cancel() {
	if (!unit_) {
		return;
	}
	if (status_ == Status::CANCELLABLE) {
		unit_->cancelConstruction();
	}
}

void NolsyOther::Suicide() {
	if (unit_) {
		UnitManager::ReturnWorker(unit_);
	}
	NolsyBase::Suicide();
}