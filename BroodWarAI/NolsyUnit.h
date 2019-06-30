#pragma once
#include "NolsyBase.h"

class NolsyUnit : public NolsyBase {
public:
	NolsyUnit(BWAPI::UnitType *unitType);
	
protected:
	void Cancel();
	void HandleUnstarted();
	void HandleCancellable() {};

private:
	BWAPI::UnitType unitType_;
};
