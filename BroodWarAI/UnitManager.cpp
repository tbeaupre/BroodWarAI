#include "UnitManager.h"

using namespace BWAPI;

BWAPI::Unitset *UnitManager::larvae_;
BWAPI::Unitset *UnitManager::workers_;
BWAPI::Unitset *UnitManager::units_;
BWAPI::Unitset *UnitManager::structures_;
BWAPI::Unitset *UnitManager::spells_;

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

void UnitManager::CompleteUnit(BWAPI::Unit unit) {
	UnitType unitType = unit->getType();

	if (unitType.isNeutral()) return; // Ignore minerals and critters

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
