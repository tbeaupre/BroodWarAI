#pragma once
#include "NolsyBase.h"

class NolsyTech : NolsyBase {
public:
	NolsyTech(const BuildAction *action);

protected:
	void Cancel();
	void HandleUnstarted();
	void HandleCancellable();

private:
	BWAPI::TechType techType_;
};
