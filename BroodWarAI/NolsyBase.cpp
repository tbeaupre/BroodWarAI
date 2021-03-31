#include "NolsyBase.h"
#include "UnitManager.h"
#include "BuildManager.h"

using namespace BWAPI;
using namespace BuildActionEnums;

void NolsyBase::Update() {
	switch (status_) {
	case UNSTARTED:
		HandleUnstarted();
		break;
	case STOPPABLE:
		HandleStoppable();
		break;
	case CANCELLABLE:
		HandleCancellable();
		break;
	}
}

void NolsyBase::OnCreateUnit() {
	UnitManager::RegisterForUnitComplete(this, unit_);
	status_ = CANCELLABLE;
}

void NolsyBase::OnDestroyUnit() {
	unit_ = nullptr;
	if (status_ != PAUSED) status_ = UNSTARTED;
}

void NolsyBase::OnMorphUnit() {
	UnitManager::RegisterForUnitComplete(this, unit_);
	status_ = CANCELLABLE;
}

void NolsyBase::OnCompleteUnit() {
	Suicide();
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
	unit_ = nullptr;
	BuildManager::CompleteAction();
}
