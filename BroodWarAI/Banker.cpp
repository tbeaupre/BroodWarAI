#include "Banker.h"
#include "UnitManager.h"
#include "PriorityQueueManager.h"

std::unordered_set<NolsyBase*> nolsies_;

void Banker::OnFrame() {

}

void Banker::CompleteAction(NolsyBase* nolsy) {

}

bool Banker::AreRequirementsFulfilled(BuildAction* nextAction) {
	switch (nextAction->getType()) {
		case ActionType::UNIT:
			return AreUnitRequirementsFulfilled(nextAction->getUnitType());
		case ActionType::TECH:
			return AreTechRequirementsFulfilled(nextAction->getTechType());
		case ActionType::UPGRADE:
			return AreUpgradeRequirementsFulfilled(nextAction->getUpgradeType());
		case ActionType::OTHER:
			return AreOtherRequirementsFulfilled(nextAction->getOtherType());
		default:
			return false;
	}
}

bool Banker::AreUnitRequirementsFulfilled(const UnitType* unitType) {
	if (Broodwar->self()->minerals() < unitType->mineralPrice()) return false;
	if (Broodwar->self()->gas() < unitType->gasPrice()) return false;
	if (Broodwar->self()->supplyTotal() - Broodwar->self()->supplyUsed() < unitType->supplyRequired()) return false;
	switch (*unitType) {
		case UnitTypes::Zerg_Devourer:
		case UnitTypes::Zerg_Guardian:
		case UnitTypes::Zerg_Lurker:
			return UnitManager::UnitOfTypeExists(unitType);
		default:
			return UnitManager::getLarvaCount() > 0;
	}
}

bool Banker::AreTechRequirementsFulfilled(const TechType* techType) {
	if (Broodwar->self()->minerals() < techType->mineralPrice()) return false;
	if (Broodwar->self()->gas() < techType->gasPrice()) return false;
	if (!UnitManager::StructureOfTypeExists(&techType->requiredUnit())) return false;
	return UnitManager::StructureOfTypeExists(&techType->whatResearches());
}

bool Banker::AreUpgradeRequirementsFulfilled(const UpgradeType* upgradeType) {
	int upgradeLevel = Broodwar->self()->getUpgradeLevel(*upgradeType);
	if (upgradeLevel == Broodwar->self()->getMaxUpgradeLevel(*upgradeType) || 
		Broodwar->self()->isUpgrading(*upgradeType)) {
		PriorityQueueManager::Pop();
		return false;
	}

	if (Broodwar->self()->minerals() < upgradeType->mineralPrice(upgradeLevel + 1)) return false;
	if (Broodwar->self()->gas() < upgradeType->gasPrice(upgradeLevel + 1)) return false;
	if (!UnitManager::StructureOfTypeExists(&upgradeType->whatsRequired(upgradeLevel + 1))) return false;
	return UnitManager::StructureOfTypeExists(&upgradeType->whatUpgrades());
}

bool Banker::AreOtherRequirementsFulfilled(const OtherActionType otherType) {
	switch (otherType) {
		case OtherActionType::EXPAND: {
			if (Broodwar->self()->minerals() < 300) return false;
			return UnitManager::getWorkerCount() > 0;
		}
		default:
			return false;
	}
}