#pragma once
#include "NolsyBase.h"

class NolsyUpgrade : NolsyBase {
public:
	NolsyUpgrade(const BuildAction *action);

protected:
	void Cancel();
	void HandleUnstarted();
	void HandleCancellable();

private :
	BWAPI::UpgradeType upgradeType_;
};
