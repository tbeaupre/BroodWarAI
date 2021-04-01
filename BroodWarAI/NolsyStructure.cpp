#include "NolsyStructure.h"
#include "UnitManager.h"

using namespace BWAPI;

NolsyStructure::NolsyStructure(UnitType unitType)
{
	unitType_ = unitType;
}

void NolsyStructure::HandleUnstarted()
{
	switch (unitType_) {
		case UnitTypes::Zerg_Greater_Spire:
		case UnitTypes::Zerg_Lair:
		case UnitTypes::Zerg_Hive:
			unit_ = UnitManager::ReserveStructure(unitType_.whatBuilds().first);
			if (unit_ && unit_->exists()) {
				if (unit_->build(unitType_)) {
					UnitManager::RegisterForUnitComplete(this, unit_);
					status_ = Status::CANCELLABLE;
				}
			}
			return;
		case UnitTypes::Zerg_Extractor:
			// This should probably be put under the Other action.
			break;
		case UnitTypes::Zerg_Creep_Colony:
			// This should probably be put under the Other action.
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
		targetLocation_ = &Broodwar->getBuildLocation(unitType_, unit_->getTilePosition());
		if (*targetLocation_ == TilePositions::Invalid) {
			targetLocation_ = nullptr;
			return; // Failed to find a place to build.
		}
	}

	if (unit_->build(unitType_, *targetLocation_)) {
		UnitManager::RegisterForUnitMorph(this, unit_);
		status_ = Status::STOPPABLE;
	}
}

void NolsyStructure::Cancel() {
	if (!unit_) {
		return; // If the build hasn't started, don't worry about canceling it.
	}
	unit_->cancelConstruction();
}

void NolsyStructure::Suicide() {
	if (unit_) {
		if (unit_->getType().isBuilding()) {
			UnitManager::ReturnStructure(unit_);
		} else {
			UnitManager::ReturnWorker(unit_);
		}
	}
	NolsyBase::Suicide();
}
