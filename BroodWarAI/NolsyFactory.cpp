#pragma once
#include "NolsyFactory.h"

using namespace std;
using namespace BuildActionEnums;

NolsyBase* createNolsy(BuildAction *action) {
	switch (action->getType) {
	case STRUCTURE:
		return new NolsyStructure(action);
	case UNIT:
		return new NolsyUnit(action->getUnitType);
	case UPGRADE:
		return new NolsyUpgrade(action);
	case TECH:
		return new NolsyTech(action);
	case OTHER:
		return new NolsyOther(action->getOtherType);
	}
}
