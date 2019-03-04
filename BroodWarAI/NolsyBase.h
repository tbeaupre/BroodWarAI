#pragma once
#include "BWAPI.h"
#include "BuildAction.h"

class NolsyBase {
public:
	void Update();

	void Create();
	void Complete();
	void Destroy();

	void SoftCancel();
	void Resume();
	void HardCancel();

protected:
	enum Status {
		PAUSED,
		UNSTARTED,
		STOPPABLE,
		CANCELLABLE
	};

	Status status_ = UNSTARTED;
	int sleep;
	const BuildAction *action_;
	BWAPI::Unit unit_;

	virtual void Cancel() = 0;
	void Suicide(); // End it all.

	virtual void HandleUnstarted() = 0;
	virtual void HandleCancellable() = 0;
};
