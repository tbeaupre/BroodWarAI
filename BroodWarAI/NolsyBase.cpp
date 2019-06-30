#include "NolsyBase.h"
#include "UnitManager.h"
#include "BuildManager.h"

using namespace BWAPI;
using namespace BuildActionEnums;

/* "Nolsy Base" as in Base Class for Nolsy, not strictly for making a new base. M8 this is your fuckin... whatever cash-in-handy-man class*/

void NolsyBase::Update() {
	switch (status_) {
	case CANCELLABLE:
		HandleCancellable();
		break;
	case UNSTARTED:
		HandleUnstarted();
		break;
	}
}

void NolsyBase::Create() {
	UnitManager::RegisterForUnitComplete(this, unit_->getType());
	status_ = CANCELLABLE;
}

void NolsyBase::Complete() {
	Suicide();
}

void NolsyBase::Destroy() {
	unit_ = nullptr;
	status_ = UNSTARTED;
}

void NolsyBase::SoftCancel() {
	Cancel();
	status_ = PAUSED;
}

void NolsyBase::Resume() {
	status_ = UNSTARTED;
}

void NolsyBase::HardCancel() {
	Cancel();
	Suicide();
}

void NolsyBase::Suicide() {
	// Alright boys, pack it up.
	BuildManager::CompleteAction();
}
