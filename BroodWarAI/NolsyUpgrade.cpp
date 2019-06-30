#include "NolsyUpgrade.h"
#include "UnitManager.h"

using namespace BWAPI;

NolsyUpgrade::NolsyUpgrade(const BuildAction *action)
{
	upgradeType_ = *action->getUpgradeType();
}

void NolsyUpgrade::Cancel()
{
	if (!unit_) {
		return; // If the build hasn't started, don't worry about canceling it.
	}
	unit_->cancelUpgrade();
}

void NolsyUpgrade::HandleUnstarted()
{
	if (Broodwar->self()->isUpgrading(upgradeType_)) {
		Broodwar << "Upgrade successfully started." << std::endl;
		sleep = upgradeType_.upgradeTime(Broodwar->self()->getUpgradeLevel(upgradeType_) + 1);
		status_ = CANCELLABLE;
		return;
	}

	if (!unit_) {
		unit_ = UnitManager::ReserveStructure(upgradeType_.whatUpgrades());
	}

	if (unit_ && unit_->exists()) {
		unit_->upgrade(upgradeType_);
	}
}

void NolsyUpgrade::HandleCancellable()
{
	if (--sleep <= 0) {
		UnitManager::ReturnStructure(unit_);
		Suicide();
	}
}
