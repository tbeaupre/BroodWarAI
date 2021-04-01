#include "NolsyBase.h"
#include "UnitManager.h"
#include "BuildManager.h"

using namespace BWAPI;
using namespace BuildActionEnums;

void NolsyBase::Update() {
	switch (status_) {
	case Status::UNSTARTED:
		HandleUnstarted();
		break;
	case Status::STOPPABLE:
		HandleStoppable();
		break;
	case Status::CANCELLABLE:
		HandleCancellable();
		break;
	}
}

void NolsyBase::OnCreateUnit() {
	UnitManager::RegisterForUnitComplete(this, unit_);
	status_ = Status::CANCELLABLE;
}

void NolsyBase::OnDestroyUnit() {
	unit_ = nullptr;
	if (status_ != Status::PAUSED) status_ = Status::UNSTARTED;
}

void NolsyBase::OnMorphUnit() {
	UnitManager::RegisterForUnitComplete(this, unit_);
	status_ = Status::CANCELLABLE;
}

void NolsyBase::OnCompleteUnit() {
	Suicide();
}

void NolsyBase::SoftCancel() {
	Cancel();
	status_ = Status::PAUSED;
}

void NolsyBase::Resume() {
	status_ = Status::UNSTARTED;
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
