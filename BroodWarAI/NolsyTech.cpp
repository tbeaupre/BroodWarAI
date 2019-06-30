#include "NolsyTech.h"
#include "UnitManager.h"

using namespace BWAPI;

NolsyTech::NolsyTech(const BuildAction *action)
{
	techType_ = *action->getTechType();
}

void NolsyTech::Cancel()
{
	if (!unit_) {
		return; // If the build hasn't started, don't worry about canceling it.
	}
	unit_->cancelResearch();
}

void NolsyTech::HandleUnstarted()
{
	if (BWAPI::Broodwar->self()->isResearching(techType_)) {
		Broodwar << "Tech successfully started." << std::endl;
		sleep = techType_.researchTime();
		status_ = CANCELLABLE;
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
	if (--sleep <= 0) {
		UnitManager::ReturnStructure(unit_);
		Suicide();
	}
}
