#pragma once
#include "NolsyBase.h"

class NolsyTech : public NolsyBase {
public:
	NolsyTech(BWAPI::TechType techType);

protected:
	void HandleUnstarted();
	void HandleCancellable();
	void Cancel();

	void Suicide();

private:
	BWAPI::TechType techType_;
	int sleep_;
};
