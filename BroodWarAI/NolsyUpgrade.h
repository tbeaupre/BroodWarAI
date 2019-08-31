#pragma once
#include "NolsyBase.h"

class NolsyUpgrade : public NolsyBase {
public:
	NolsyUpgrade(BWAPI::UpgradeType upgradeType);

protected:
	void HandleUnstarted();
	void HandleCancellable();
	void Cancel();

	void Suicide();

private :
	BWAPI::UpgradeType upgradeType_;
	int sleep_;
};
