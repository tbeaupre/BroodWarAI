#pragma once
#include "NolsyFactory.h"
#include <exception>

using namespace std;
using namespace BuildActionEnums;

static NolsyBase *createNolsy(BuildAction *action) {
	NolsyBase *mike_nolan;
	switch (action->getType()) {
	case STRUCTURE:
		mike_nolan = new NolsyStructure(action);
		break;
	case UNIT:
		mike_nolan = new NolsyUnit(action->getUnitType());
		break;
	case UPGRADE:
		mike_nolan = new NolsyUpgrade(action);
		break;
	case TECH:
		mike_nolan = new NolsyTech(action);
		break;
	case OTHER:
		mike_nolan = new NolsyOther(action->getOtherType());
		break;
	default:
		BWAPI::Broodwar << "ah fuck off cunt";
		return nullptr;
	}
	mike_nolan->Create();
	return mike_nolan;
}