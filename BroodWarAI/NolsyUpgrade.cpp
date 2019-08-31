#include "NolsyUpgrade.h"
#include "UnitManager.h"

using namespace BWAPI;

NolsyUpgrade::NolsyUpgrade(BWAPI::UpgradeType upgradeType)
{
	upgradeType_ = upgradeType;
}

void NolsyUpgrade::HandleUnstarted()
{
	if (Broodwar->self()->isUpgrading(upgradeType_)) {
		Broodwar << "Upgrade successfully started." << std::endl;
		sleep_ = upgradeType_.upgradeTime(Broodwar->self()->getUpgradeLevel(upgradeType_) + 1);
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
	if (--sleep_ <= 0) {
		Suicide();
	}
}

void NolsyUpgrade::Cancel() {
	if (!unit_) {
		return; // If the build hasn't started, don't worry about canceling it.
	}
	unit_->cancelUpgrade();
}

void NolsyUpgrade::Suicide() {
	if (unit_) {
		UnitManager::ReturnStructure(unit_);
	}
	NolsyBase::Suicide();
}
