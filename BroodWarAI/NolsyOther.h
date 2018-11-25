#pragma once
#include "NolsyBase.h"

class NolsyOther : NolsyBase {
public:
	NolsyOther(const BuildAction *action);

protected:
	void Cancel() {};
	void HandleUnstarted() {};
	void HandleCancellable() {};

private:
	BuildActionEnums::OtherActionType otherType_;
};
