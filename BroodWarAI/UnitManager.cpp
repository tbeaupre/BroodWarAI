#include "UnitManager.h"

using namespace BWAPI;

BWAPI::Unitset *UnitManager::larvae_;
BWAPI::Unitset *UnitManager::workers_;
BWAPI::Unitset *UnitManager::units_;
BWAPI::Unitset *UnitManager::structures_;
BWAPI::Unitset *UnitManager::spells_;
std::map<BWAPI::Unit, NolsyBase*> UnitManager::unitCreateRegistry_;
std::map<BWAPI::Unit, NolsyBase*> UnitManager::unitCompleteRegistry_;

void UnitManager::Init() {
	larvae_ = new Unitset(Unitset::none);
	workers_ = new Unitset(Unitset::none);
	units_ = new Unitset(Unitset::none);
	structures_ = new Unitset(Unitset::none);
	spells_ = new Unitset(Unitset::none);
}

BWAPI::Unit UnitManager::ReserveLarva() {
	if (larvae_->empty()) {
		return nullptr;
	}

	Unit toReturn = *larvae_->begin();
	larvae_->erase(larvae_->begin());
	return toReturn;
}

void UnitManager::ReturnLarva(BWAPI::Unit larva) {
	larvae_->insert(larva);
	UnregisterForUnitComplete(larva);
}

BWAPI::Unit UnitManager::ReserveWorker() {
	if (workers_->empty()) return nullptr;

	Unit toReturn = *workers_->begin();
	workers_->erase(workers_->begin());
	return toReturn;
}

void UnitManager::ReturnWorker(BWAPI::Unit worker) {
	workers_->insert(worker);
	UnregisterForUnitCreate(worker);
}

BWAPI::Unit UnitManager::ReserveStructure(BWAPI::UnitType structureType) {
	if (structures_->empty()) return nullptr;

	Unit toReturn = structures_->getClosestUnit(Filter::GetType == structureType);
	structures_->erase(toReturn);
	return toReturn;
}

void UnitManager::ReturnStructure(BWAPI::Unit structure) {
	structures_->insert(structure);
	UnregisterForUnitComplete(structure);
}

BWAPI::Unit UnitManager::ReserveUnit(BWAPI::UnitType unitType) {
	if (units_->empty()) return nullptr;

	Unit toReturn = units_->getClosestUnit(Filter::GetType == unitType);
	units_->erase(toReturn);
	return toReturn;
}

void UnitManager::ReturnUnit(BWAPI::Unit unit) {
	units_->insert(unit);
	UnregisterForUnitComplete(unit);
}

void UnitManager::RegisterForUnitCreate(NolsyBase *nolsy, BWAPI::Unit unit) {
	unitCreateRegistry_[unit] = nolsy;
}

void UnitManager::RegisterForUnitComplete(NolsyBase *nolsy, BWAPI::Unit unit) {
	unitCompleteRegistry_[unit] = nolsy;
}

void UnitManager::UnregisterForUnitCreate(BWAPI::Unit unit) {
	unitCreateRegistry_.erase(unit);
}

void UnitManager::UnregisterForUnitComplete(BWAPI::Unit unit) {
	unitCompleteRegistry_.erase(unit);
}

void UnitManager::CreateUnit(BWAPI::Unit unit) {
	auto nolsySetIter = unitCreateRegistry_.find(unit);
	if (nolsySetIter != unitCreateRegistry_.end()) {
		(*nolsySetIter).second->OnCreateUnit();
		UnregisterForUnitCreate(unit);
	}
}

void UnitManager::CompleteUnit(BWAPI::Unit unit) {
	UnitType unitType = unit->getType();
	BWAPI::Broodwar->drawTextScreen(50, 40, "Unit Complete: %s", unitType.c_str());
	if (unitType.isNeutral()) return; // Ignore minerals and critters

	auto nolsySetIter = unitCompleteRegistry_.find(unit);
	if (nolsySetIter != unitCompleteRegistry_.end()) {
		(*nolsySetIter).second->OnCompleteUnit();
		UnregisterForUnitComplete(unit);
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

	auto nolsySetIter = unitCompleteRegistry_.find(unit);
	if (nolsySetIter != unitCompleteRegistry_.end()) {
		(*nolsySetIter).second->OnDestroyUnit();
		UnregisterForUnitComplete(unit);
	} else {
		nolsySetIter = unitCreateRegistry_.find(unit);
		if (nolsySetIter != unitCreateRegistry_.end()) {
			(*nolsySetIter).second->OnDestroyUnit();
			UnregisterForUnitCreate(unit);
		}
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

size_t *UnitManager::GetCounts() {
	return new size_t[4] {
		larvae_->size(),
		workers_->size(),
		units_->size(),
		structures_->size()
	};
}
