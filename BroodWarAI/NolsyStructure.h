#pragma once
#include "NolsyBase.h"

class NolsyStructure : public NolsyBase {
public:
	NolsyStructure(const BuildAction *action);

protected:
	void Cancel();
	void HandleUnstarted();
	void HandleCancellable() {};

private:
	BWAPI::UnitType unitType_;
	BWAPI::TilePosition *targetLocation_;
};
