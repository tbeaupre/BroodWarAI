#include "NolsyFactory.h"
#include "NolsyOther.h"
#include "NolsyStructure.h"
#include "NolsyTech.h"
#include "NolsyUnit.h"
#include "NolsyUpgrade.h"

using namespace BuildActionEnums;

NolsyBase *NolsyFactory::BuildNolsy(const BuildAction *action) {
	switch (action->getType()) {
		case ActionType::OTHER:
			return new NolsyOther(action->getOtherType());
		case ActionType::TECH:
			return new NolsyTech(*action->getTechType());
		case ActionType::UNIT:
			if (action->isBuilding()) {
				return new NolsyUnit(*action->getUnitType());
			} else {
				return new NolsyStructure(*action->getUnitType());
			}
		case ActionType::UPGRADE:
			return new NolsyUpgrade(*action->getUpgradeType());
		default:
			return nullptr;
	}
}