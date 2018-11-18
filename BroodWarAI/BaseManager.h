#pragma once
#include "BWEM 1.4.1\src\bwem.h"

typedef std::vector<const BWEM::Base*> BaseVector;

class BaseManager {
public:
	BaseManager(BWAPI::TilePosition startingPos);

private:
	BWAPI::TilePosition startPos_;
	BaseVector availableBases_;
	BaseVector currentBases_;
};