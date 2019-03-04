#pragma once
#include "BWEM 1.4.1\src\bwem.h"

typedef std::vector<const BWEM::Base*> BaseVector;

class BaseManager {
public:
	static void Init(BWAPI::TilePosition startingPos);
	static BWAPI::TilePosition GetNextBasePosition();
	static void TakeNextBase();
	static BaseVector getCurrentBases() { return currentBases_; }

private:
	static BaseVector availableBases_;
	static BaseVector currentBases_;
};
