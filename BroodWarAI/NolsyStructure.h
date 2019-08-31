#pragma once
#include "NolsyBase.h"

class NolsyStructure : public NolsyBase {
public:
	NolsyStructure(UnitType unitType);

protected:
	void HandleUnstarted();
	void Cancel();

	void Suicide();

private:
	BWAPI::UnitType unitType_;
	BWAPI::TilePosition *targetLocation_;
};
