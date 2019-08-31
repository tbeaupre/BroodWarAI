#pragma once
#include "BuildAction.h"
#include "NolsyBase.h"

class NolsyFactory {
public:
	static NolsyBase *BuildNolsy(const BuildAction *action)
};
