#include "NolsyUnit.h"
#include "UnitManager.h"

using namespace BWAPI;

NolsyUnit::NolsyUnit(UnitType unitType)
{
	unitType_ = unitType;
}

void NolsyUnit::HandleUnstarted()
{
	if (!(unit_ && unit_->exists())) {
		switch (unitType_) {
		case UnitTypes::Zerg_Devourer:
		case UnitTypes::Zerg_Guardian:
		case UnitTypes::Zerg_Lurker:
			unit_ = UnitManager::ReserveUnit(unitType_.whatBuilds().first);
			break;
		default:
			BWAPI::Broodwar << "Reserving Larva" << std::endl;
			unit_ = UnitManager::ReserveLarva();
			break;
		}
	}

	if (unit_ && unit_->exists()) {
		if (unit_->morph(unitType_)) {
			UnitManager::RegisterForUnitComplete(this, unit_);
			status_ = CANCELLABLE;
		}
	}
}

void NolsyUnit::Cancel() {
	if (!unit_) {
		return; // If the build hasn't started, don't worry about canceling it.
	}
	unit_->cancelMorph();
}

void NolsyUnit::Suicide() {
	if (unit_ && unit_->getType() != UnitTypes::Zerg_Larva) {
		UnitManager::ReturnUnit(unit_);
	}
	NolsyBase::Suicide();
}
