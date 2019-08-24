#pragma once
#include "NolsyBase.h"

class NolsyOther : public NolsyBase {
public:
	NolsyOther(BuildActionEnums::OtherActionType otherType);

	void OnCompleteUnit();

protected:
	void HandleUnstarted();
	void HandleStoppable();
	void Cancel();

	void Suicide();

private:
	BuildActionEnums::OtherActionType otherType_;
	BWAPI::TilePosition *targetLocation_;
};
