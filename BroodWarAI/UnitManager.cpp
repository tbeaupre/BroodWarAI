#include "UnitManager.h"

using namespace BWAPI;

BWAPI::Unitset *UnitManager::larvae_;
BWAPI::Unitset *UnitManager::workers_;
BWAPI::Unitset *UnitManager::units_;
BWAPI::Unitset *UnitManager::structures_;
BWAPI::Unitset *UnitManager::spells_;
std::map<BWAPI::UnitType, std::unordered_set<Nolsy*>> UnitManager::unitCreateRegistry_;
std::map<BWAPI::UnitType, std::unordered_set<Nolsy*>> UnitManager::unitCompleteRegistry_;
std::map<BWAPI::UnitType, std::unordered_set<Nolsy*>> UnitManager::unitDestroyRegistry_;

void UnitManager::Init() {
	larvae_ = new Unitset(Unitset::none);
	workers_ = new Unitset(Unitset::none);
	units_ = new Unitset(Unitset::none);
	structures_ = new Unitset(Unitset::none);
	spells_ = new Unitset(Unitset::none);
}

BWAPI::Unit UnitManager::GetLarva() {
	if (larvae_->empty()) return nullptr;

	Unit toReturn = *larvae_->begin();
	larvae_->erase(larvae_->begin());
	return toReturn;
}

BWAPI::Unit UnitManager::ReserveWorker() {
	if (workers_->empty()) return nullptr;

	Unit toReturn = *workers_->begin();
	workers_->erase(workers_->begin());
	return toReturn;
}

void UnitManager::ReturnWorker(BWAPI::Unit worker) {
	workers_->insert(worker);
}

BWAPI::Unit UnitManager::ReserveStructure(BWAPI::UnitType structureType) {
	if (structures_->empty()) return nullptr;

	Unit toReturn = structures_->getClosestUnit(Filter::GetType == structureType);
	structures_->erase(toReturn);
	return toReturn;
}

void UnitManager::ReturnStructure(BWAPI::Unit structure) {
	structures_->insert(structure);
}

BWAPI::Unit UnitManager::ReserveUnit(BWAPI::UnitType unitType) {
	if (units_->empty()) return nullptr;

	Unit toReturn = units_->getClosestUnit(Filter::GetType == unitType);
	units_->erase(toReturn);
	return toReturn;
}

void UnitManager::ReturnUnit(BWAPI::Unit unit) {
	units_->insert(unit);
}

void UnitManager::RegisterForUnitCreate(Nolsy *nolsy, BWAPI::UnitType unitType) {
	unitCreateRegistry_[unitType].insert(nolsy);
}

void UnitManager::RegisterForUnitComplete(Nolsy *nolsy, BWAPI::UnitType unitType) {
	unitCompleteRegistry_[unitType].insert(nolsy);
}

void UnitManager::RegisterForUnitDestroy(Nolsy *nolsy, BWAPI::UnitType unitType) {
	unitDestroyRegistry_[unitType].insert(nolsy);
}

void UnitManager::CreateUnit(BWAPI::Unit unit) {
	auto nolsySetIter = unitCreateRegistry_.find(unit->getType());
	if (nolsySetIter != unitCreateRegistry_.end()) {
		(*(*nolsySetIter).second.begin())->Create();
	}
}

void UnitManager::CompleteUnit(BWAPI::Unit unit) {
	UnitType unitType = unit->getType();
	if (unitType.isNeutral()) return; // Ignore minerals and critters

	auto nolsySetIter = unitCompleteRegistry_.find(unitType);
	if (nolsySetIter != unitCompleteRegistry_.end()) {
		// Need to go from iterator -> pair -> unordered_set -> nolsy, so this looks pretty gnarly...
		(*(*nolsySetIter).second.begin())->Complete();
	}

	if (unitType == UnitTypes::Zerg_Larva) {
		larvae_->insert(unit);
	} else if (unitType == UnitTypes::Zerg_Drone) {
		workers_->insert(unit);
	} else if (unitType.isBuilding()) {
		structures_->insert(unit);
	} else if (unitType.isSpell()) {
		spells_->insert(unit); // Only for dark swarms.
	} else {
		units_->insert(unit); // Only applicable to zerglings and scourge.
	}
}

void UnitManager::DestroyUnit(BWAPI::Unit unit) {
	UnitType unitType = unit->getType();
	if (unitType.isNeutral()) return; // Ignore minerals and critters

	auto nolsySetIter = unitDestroyRegistry_.find(unitType);
	if (nolsySetIter != unitDestroyRegistry_.end()) {
		// Need to go from iterator -> pair -> unordered_set -> nolsy, so this looks pretty gnarly...
		(*(*nolsySetIter).second.begin())->Destroy();
	}

	if (unitType == UnitTypes::Zerg_Drone) {
		workers_->erase(unit);
	} else if (unitType.isBuilding()) {
		structures_->erase(unit);
	} else if (unitType.isSpell()) {
		spells_->erase(unit); // Only for dark swarms.
	} else {
		units_->erase(unit);
	}
}
