#pragma once
#include "BWAPI.h"

class UnitManager {
public:
	static void Init();

	static BWAPI::Unit GetLarva();
	static BWAPI::Unit ReserveWorker();
	static void ReturnWorker(BWAPI::Unit worker);
	static BWAPI::Unit ReserveStructure(BWAPI::UnitType structureType);
	static void ReturnStructure(BWAPI::Unit structure);

	static void CompleteUnit(BWAPI::Unit unit);
	static void DestroyUnit(BWAPI::Unit unit);

private:
	static BWAPI::Unitset *larvae_;
	static BWAPI::Unitset *workers_;
	static BWAPI::Unitset *units_;
	static BWAPI::Unitset *structures_;
	static BWAPI::Unitset *spells_;
};