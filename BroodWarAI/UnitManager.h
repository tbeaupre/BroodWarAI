#pragma once
#include "BWAPI.h"
#include "NolsyBase.h"

using namespace BWAPI;

class UnitManager {
public:
	static int getLarvaCount() { return larvae_->size(); }
	static int getWorkerCount() { return workers_->size(); }

	static void Init();

	static Unit ReserveLarva();
	static void ReturnLarva(Unit larva);

	static Unit ReserveWorker();
	static void ReturnWorker(Unit worker);

	static Unit ReserveStructure(UnitType structureType);
	static void ReturnStructure(Unit structure);

	static Unit ReserveUnit(UnitType unitType);
	static void ReturnUnit(Unit unit);

	static void RegisterForUnitCreate(NolsyBase *nolsy, Unit unit);
	static void RegisterForUnitMorph(NolsyBase* nolsy, Unit unit);
	static void RegisterForUnitComplete(NolsyBase *nolsy, Unit unit);
	static void UnregisterForUnitCreate(Unit unit);
	static void UnregisterForUnitMorph(Unit unit);
	static void UnregisterForUnitComplete(Unit unit);

	static void CreateUnit(Unit unit); // Only ever called when larva are created.
	static void DestroyUnit(Unit unit);
	static void MorphUnit(Unit unit);
	static void CompleteUnit(Unit unit);

	static bool UnitOfTypeExists(const UnitType *unitType);
	static bool StructureOfTypeExists(const UnitType* unitType);

	static size_t *GetCounts(); // DEBUG

private:
	static Unitset *larvae_;
	static Unitset *workers_;
	static Unitset *units_;
	static Unitset *structures_;
	static Unitset *spells_;

	static std::map<Unit, NolsyBase*> unitCreateRegistry_;
	static std::map<Unit, NolsyBase*> unitMorphRegistry_;
	static std::map<Unit, NolsyBase*> unitCompleteRegistry_;
};