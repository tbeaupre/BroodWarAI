#pragma once
#include "BWEM 1.4.1\src\bwem.h"

typedef std::vector<BWAPI::TilePosition *> BaseVector;

class BaseManager {
public:
	static void Init(BWAPI::TilePosition startingPos);
	static BWAPI::TilePosition *GetNextBaseTilePosition();
	static void TakeNextBase();
	static BaseVector getCurrentBases() { return currentBases_; }

private:
	static BaseVector availableBases_;
	static BaseVector currentBases_;
};
