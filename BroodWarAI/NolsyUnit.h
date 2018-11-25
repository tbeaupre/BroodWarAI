#pragma once
#include "NolsyBase.h"

class NolsyUnit : NolsyBase {
public:
	NolsyUnit(const BuildAction *action);
	
protected:
	void Cancel();
	void HandleUnstarted();
	void HandleCancellable() {};

private:
	BWAPI::UnitType unitType_;
};
