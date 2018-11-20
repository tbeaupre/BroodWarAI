#pragma once
#include "BWAPI.h"
#include "Nolsy.h"

class UnitManager {
public:
	static void Init();

	static BWAPI::Unit GetLarva();

	static BWAPI::Unit ReserveWorker();
	static void ReturnWorker(BWAPI::Unit worker);

	static BWAPI::Unit ReserveStructure(BWAPI::UnitType structureType);
	static void ReturnStructure(BWAPI::Unit structure);

	static BWAPI::Unit ReserveUnit(BWAPI::UnitType unitType);
	static void ReturnUnit(BWAPI::Unit unit);

	static void RegisterForUnitCreate(Nolsy *nolsy, BWAPI::UnitType unitType);
	static void RegisterForUnitComplete(Nolsy *nolsy, BWAPI::UnitType unitType);
	static void RegisterForUnitDestroy(Nolsy *nolsy, BWAPI::UnitType unitType);

	static void CreateUnit(BWAPI::Unit unit);
	static void CompleteUnit(BWAPI::Unit unit);
	static void DestroyUnit(BWAPI::Unit unit);

private:
	static BWAPI::Unitset *larvae_;
	static BWAPI::Unitset *workers_;
	static BWAPI::Unitset *units_;
	static BWAPI::Unitset *structures_;
	static BWAPI::Unitset *spells_;

	static std::map<BWAPI::UnitType, std::unordered_set<Nolsy*>> unitCreateRegistry_;
	static std::map<BWAPI::UnitType, std::unordered_set<Nolsy*>> unitCompleteRegistry_;
	static std::map<BWAPI::UnitType, std::unordered_set<Nolsy*>> unitDestroyRegistry_;
};