#pragma once
#include "NolsyBase.h"

class NolsyUnit : public NolsyBase {
public:
	NolsyUnit(BWAPI::UnitType unitType);
	
protected:
	void HandleUnstarted();
	void Cancel();

	void Suicide();

private:
	BWAPI::UnitType unitType_;
};
