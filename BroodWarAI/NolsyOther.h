#pragma once
#include "NolsyBase.h"

class NolsyOther : public NolsyBase {
public:
	NolsyOther(BuildActionEnums::OtherActionType otherType);

	void Complete();

protected:
	void Cancel();
	void HandleUnstarted();
	void HandleCancellable();

private:
	BuildActionEnums::OtherActionType otherType_;
	BWAPI::TilePosition *targetLocation_;
};
