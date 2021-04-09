#include "UnitManager.h"

using namespace BWAPI;

Unitset *UnitManager::larvae_;
Unitset *UnitManager::workers_;
Unitset *UnitManager::units_;
Unitset *UnitManager::structures_;
Unitset *UnitManager::spells_;
std::map<Unit, NolsyBase*> UnitManager::unitCreateRegistry_;
std::map<Unit, NolsyBase*> UnitManager::unitMorphRegistry_;
std::map<Unit, NolsyBase*> UnitManager::unitCompleteRegistry_;

void UnitManager::Init() {
	larvae_ = new Unitset(Unitset::none);
	workers_ = new Unitset(Unitset::none);
	units_ = new Unitset(Unitset::none);
	structures_ = new Unitset(Unitset::none);
	spells_ = new Unitset(Unitset::none);
}

Unit UnitManager::ReserveLarva() {
	if (larvae_->empty()) {
		return nullptr;
	}

	Unit toReturn = *larvae_->begin();
	larvae_->erase(larvae_->begin());
	return toReturn;
}

void UnitManager::ReturnLarva(Unit larva) {
	larvae_->insert(larva);
	UnregisterForUnitComplete(larva);
}

Unit UnitManager::ReserveWorker() {
	if (workers_->empty()) return nullptr;

	Unit toReturn = *workers_->begin();
	workers_->erase(workers_->begin());
	return toReturn;
}

void UnitManager::ReturnWorker(Unit worker) {
	workers_->insert(worker);
	UnregisterForUnitCreate(worker);
}

Unit UnitManager::ReserveStructure(UnitType structureType) {
	if (structures_->empty()) return nullptr;

	Unit toReturn = structures_->getClosestUnit(Filter::GetType == structureType);
	structures_->erase(toReturn);
	return toReturn;
}

void UnitManager::ReturnStructure(Unit structure) {
	structures_->insert(structure);
	UnregisterForUnitComplete(structure);
}

Unit UnitManager::ReserveUnit(UnitType unitType) {
	if (units_->empty()) return nullptr;

	Unit toReturn = units_->getClosestUnit(Filter::GetType == unitType);
	units_->erase(toReturn);
	return toReturn;
}

void UnitManager::ReturnUnit(Unit unit) {
	units_->insert(unit);
	UnregisterForUnitComplete(unit);
}

void UnitManager::RegisterForUnitCreate(NolsyBase *nolsy, Unit unit) {
	unitCreateRegistry_[unit] = nolsy;
}

void UnitManager::RegisterForUnitMorph(NolsyBase* nolsy, Unit unit) {
	unitMorphRegistry_[unit] = nolsy;
}

void UnitManager::RegisterForUnitComplete(NolsyBase *nolsy, Unit unit) {
	unitCompleteRegistry_[unit] = nolsy;
}

void UnitManager::UnregisterForUnitCreate(Unit unit) {
	unitCreateRegistry_.erase(unit);
}

void UnitManager::UnregisterForUnitMorph(Unit unit) {
	unitCreateRegistry_.erase(unit);
}

void UnitManager::UnregisterForUnitComplete(Unit unit) {
	unitCompleteRegistry_.erase(unit);
}

void UnitManager::CreateUnit(Unit unit) {
	auto nolsySetIter = unitCreateRegistry_.find(unit);
	if (nolsySetIter != unitCreateRegistry_.end()) {
		(*nolsySetIter).second->OnCreateUnit();
		UnregisterForUnitCreate(unit);
	}
}

void UnitManager::DestroyUnit(Unit unit) {
	UnitType unitType = unit->getType();
	if (unitType.isNeutral()) return; // Ignore minerals and critters

	auto nolsySetIter = unitCompleteRegistry_.find(unit);
	if (nolsySetIter != unitCompleteRegistry_.end()) {
		(*nolsySetIter).second->OnDestroyUnit();
		UnregisterForUnitComplete(unit);
	}
	else {
		nolsySetIter = unitCreateRegistry_.find(unit);
		if (nolsySetIter != unitCreateRegistry_.end()) {
			(*nolsySetIter).second->OnDestroyUnit();
			UnregisterForUnitCreate(unit);
		}
	}

	if (unitType == UnitTypes::Zerg_Drone) {
		workers_->erase(unit);
	}
	else if (unitType.isBuilding()) {
		structures_->erase(unit);
	}
	else if (unitType.isSpell()) {
		spells_->erase(unit); // Only for dark swarms.
	}
	else {
		units_->erase(unit);
	}
}

void UnitManager::MorphUnit(Unit unit) {
	auto nolsySetIter = unitMorphRegistry_.find(unit);
	if (nolsySetIter != unitMorphRegistry_.end()) {
		(*nolsySetIter).second->OnMorphUnit();
		UnregisterForUnitMorph(unit);
	}
}

void UnitManager::CompleteUnit(Unit unit) {
	UnitType unitType = unit->getType();
	Broodwar->drawTextScreen(50, 40, "Unit Complete: %s", unitType.c_str());
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

bool UnitManager::UnitOfTypeExists(const UnitType *unitType) {
	for (auto unit : *units_) {
		if (unit->getType() == *unitType) {
			return true;
		}
	}

	return false;
}

bool UnitManager::StructureOfTypeExists(const UnitType* unitType) {
	for (auto structure : *structures_) {
		if (structure->getType() == *unitType) {
			return true;
		}
	}

	return false;
}

size_t *UnitManager::GetCounts() {
	return new size_t[4] {
		larvae_->size(),
		workers_->size(),
		units_->size(),
		structures_->size()
	};
}
