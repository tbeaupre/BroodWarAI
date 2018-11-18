#pragma once
#include "BWAPI.h"
#include "BuildAction.h"

class Nolsy {
public:
	Nolsy(const BuildAction *action);
	void Update();
	void SoftCancel();
	void Resume();
	void HardCancel();

private:
	enum Status {
		PAUSED,
		STOPPABLE,
		CANCELLABLE
	};

	Status status_ = STOPPABLE;
	const BuildAction *action_;
	BWAPI::Unit target_;

	void Cancel();
	void Suicide(); // End it all.

	void HandleAction();
	void HandleUnitAction(const BWAPI::UnitType *unitType);
	void HandleStructureAction(const BWAPI::UnitType *unitType);
	void HandleTechAction(const BWAPI::TechType *techType);
	void HandleUpgradeAction(const BWAPI::UpgradeType *upgradeType);
	void HandleOtherAction(const BuildActionEnums::OtherActionType otherType);
};