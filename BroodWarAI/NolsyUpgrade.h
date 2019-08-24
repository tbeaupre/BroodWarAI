#pragma once
#include "NolsyBase.h"

class NolsyUpgrade : NolsyBase {
public:
	NolsyUpgrade(const BuildAction *action);

protected:
	void HandleUnstarted();
	void HandleCancellable();
	void Cancel();

	void Suicide();

private :
	BWAPI::UpgradeType upgradeType_;
	int sleep_;
};
