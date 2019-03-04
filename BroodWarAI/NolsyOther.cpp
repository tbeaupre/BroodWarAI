#include "NolsyOther.h"
#include "UnitManager.h"
#include "BaseManager.h"

using namespace BWAPI;
using namespace BuildActionEnums;

NolsyOther::NolsyOther(BuildActionEnums::OtherActionType otherType)
{
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

void NolsyOther::HandleUnstarted()
{
	switch (otherType_) {
		case OtherActionType::EXPAND:
			break;
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
		targetLocation_ = &BaseManager::GetNextBasePosition();
		if (*targetLocation_ == TilePositions::Invalid) {
			targetLocation_ = nullptr;
			return; // Failed to find a place to build.
		}
	}

	// NEED TO EXPLORE LOCATION FIRST!

	if (unit_->build(UnitTypes::Zerg_Hatchery, *targetLocation_)) {
		UnitManager::RegisterForUnitCreate(this, UnitTypes::Zerg_Hatchery);
		UnitManager::RegisterForUnitDestroy(this, unit_->getType());
		status_ = STOPPABLE;
	}
}