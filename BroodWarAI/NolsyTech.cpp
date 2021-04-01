#include "NolsyTech.h"
#include "UnitManager.h"

using namespace BWAPI;

NolsyTech::NolsyTech(BWAPI::TechType techType)
{
	techType_ = techType;
}

void NolsyTech::HandleUnstarted()
{
	if (BWAPI::Broodwar->self()->isResearching(techType_)) {
		Broodwar << "Tech successfully started." << std::endl;
		sleep_ = techType_.researchTime();
		status_ = Status::CANCELLABLE;
		return;
	}

	if (!unit_) {
		unit_ = UnitManager::ReserveStructure(techType_.whatResearches());
	}

	if (unit_ && unit_->exists()) {
		unit_->research(techType_);
	}
}

void NolsyTech::HandleCancellable()
{
	if (--sleep_ <= 0) {
		UnitManager::ReturnStructure(unit_);
		Suicide();
	}
}

void NolsyTech::Cancel() {
	if (!unit_) {
		return; // If the build hasn't started, don't worry about canceling it.
	}
	unit_->cancelResearch();
}

void NolsyTech::Suicide() {
	if (unit_) {
		UnitManager::ReturnStructure(unit_);
	}
	NolsyBase::Suicide();
}
