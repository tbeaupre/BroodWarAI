#include "BaseManager.h"

using namespace BWAPI;

BaseVector BaseManager::availableBases_;
BaseVector BaseManager::currentBases_;

void BaseManager::Init(TilePosition startPos) {
	for (const BWEM::Area &area : BWEM::Map::Instance().Areas()) {
		for (const BWEM::Base &base : area.Bases()) {
			availableBases_.push_back(new BWAPI::TilePosition(base.Location()));
		}
	}

	std::sort(availableBases_.begin(), availableBases_.end(), [&startPos](TilePosition *a, TilePosition *b) {
		return (a->getDistance(startPos) > b->getDistance(startPos));
	});

	TakeNextBase(); // Need to take your starting base.
}

BWAPI::TilePosition *BaseManager::GetNextBaseTilePosition() {
	if (availableBases_.empty()) {
		return nullptr;
		Broodwar << "NO MORE BASES TO TAKE!" << std::endl;
	}
	return availableBases_.back();
}

void BaseManager::TakeNextBase() {
	currentBases_.push_back(availableBases_.back());
	availableBases_.pop_back();
}
