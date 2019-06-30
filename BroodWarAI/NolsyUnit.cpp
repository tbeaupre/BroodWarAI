#include "NolsyUnit.h"
#include "UnitManager.h"

using namespace BWAPI;

static int nolsyCount = 0;

NolsyUnit::NolsyUnit(UnitType *unitType)
{
	Broodwar << "[" << nolsyCount << "]NolsyUnit::NolsyUnit: " << unitType->toString() << std::endl;
	nolsyCount++;
	unitType_ = *unitType;
}

void NolsyUnit::Cancel()
{
	if (!unit_) {
		return; // If the build hasn't started, don't worry about canceling it.
	}
	unit_->cancelMorph();
}

void NolsyUnit::HandleUnstarted()
{
	Unit source;

	switch (unitType_) {
	case UnitTypes::Zerg_Devourer:
	case UnitTypes::Zerg_Guardian:
	case UnitTypes::Zerg_Lurker:
		source = UnitManager::ReserveUnit(unitType_.whatBuilds().first);
		break;
	default:
		source = UnitManager::ReserveLarva();
		break;
	}

	if (source && source->exists()) {
		if (source->morph(unitType_)) {
			unit_ = source;
			UnitManager::RegisterForUnitComplete(this, unitType_);
			UnitManager::RegisterForUnitDestroy(this, unitType_);
			status_ = CANCELLABLE;
		} else {
			Broodwar << "NolsyUnit::HandleUnstarted(): Could not morph unit." << std::endl;
			UnitManager::ReturnLarva(source); // Assumes the source was a larva.
		}
	}
}
