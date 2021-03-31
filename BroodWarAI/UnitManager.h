#pragma once
#include "BWAPI.h"
#include "NolsyBase.h"

class UnitManager {
public:
	static void Init();

	static BWAPI::Unit ReserveLarva();
	static void ReturnLarva(BWAPI::Unit larva);

	static BWAPI::Unit ReserveWorker();
	static void ReturnWorker(BWAPI::Unit worker);

	static BWAPI::Unit ReserveStructure(BWAPI::UnitType structureType);
	static void ReturnStructure(BWAPI::Unit structure);

	static BWAPI::Unit ReserveUnit(BWAPI::UnitType unitType);
	static void ReturnUnit(BWAPI::Unit unit);

	static void RegisterForUnitCreate(NolsyBase *nolsy, BWAPI::Unit unit);
	static void RegisterForUnitMorph(NolsyBase* nolsy, BWAPI::Unit unit);
	static void RegisterForUnitComplete(NolsyBase *nolsy, BWAPI::Unit unit);
	static void UnregisterForUnitCreate(BWAPI::Unit unit);
	static void UnregisterForUnitMorph(BWAPI::Unit unit);
	static void UnregisterForUnitComplete(BWAPI::Unit unit);

	static void CreateUnit(BWAPI::Unit unit); // Only ever called when larva are created.
	static void DestroyUnit(BWAPI::Unit unit);
	static void MorphUnit(BWAPI::Unit unit);
	static void CompleteUnit(BWAPI::Unit unit);

	static size_t *GetCounts(); // DEBUG

private:
	static BWAPI::Unitset *larvae_;
	static BWAPI::Unitset *workers_;
	static BWAPI::Unitset *units_;
	static BWAPI::Unitset *structures_;
	static BWAPI::Unitset *spells_;

	static std::map<BWAPI::Unit, NolsyBase*> unitCreateRegistry_;
	static std::map<BWAPI::Unit, NolsyBase*> unitMorphRegistry_;
	static std::map<BWAPI::Unit, NolsyBase*> unitCompleteRegistry_;
};