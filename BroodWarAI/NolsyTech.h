#pragma once
#include "NolsyBase.h"

class NolsyTech : NolsyBase {
public:
	NolsyTech(const BuildAction *action);

protected:
	void HandleUnstarted();
	void HandleCancellable();
	void Cancel();

	void Suicide();

private:
	BWAPI::TechType techType_;
	int sleep_;
};
