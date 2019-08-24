#pragma once
#include "NolsyBase.h"

class NolsyStructure : NolsyBase {
public:
	NolsyStructure(const BuildAction *action);

protected:
	void HandleUnstarted();
	void Cancel();

	void Suicide();

private:
	BWAPI::UnitType unitType_;
	BWAPI::TilePosition *targetLocation_;
};
