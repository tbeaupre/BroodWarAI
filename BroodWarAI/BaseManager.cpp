#include "BaseManager.h"

using namespace BWAPI;

BaseVector BaseManager::availableBases_;
BaseVector BaseManager::currentBases_;

void BaseManager::Init(TilePosition startPos) {
	startPos;
	for (const BWEM::Area &area : BWEM::Map::Instance().Areas()) {
		for (const BWEM::Base &base : area.Bases()) {
			availableBases_.push_back(&base);
		}
	}

	std::sort(availableBases_.begin(), availableBases_.end(), [&startPos](const BWEM::Base *a, const BWEM::Base *b) {
		return (a->Location().getDistance(startPos) < b->Location().getDistance(startPos));
	});
}

BWAPI::TilePosition BaseManager::GetNextBasePosition() {
	return availableBases_.back()->Location();
}

void BaseManager::TakeNextBase() {
	currentBases_.push_back(availableBases_.back());
	availableBases_.pop_back();
}
