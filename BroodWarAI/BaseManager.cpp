#include "BaseManager.h"

using namespace BWAPI;

BaseManager::BaseManager(TilePosition startPos) {
	startPos_ = startPos;
	for (const BWEM::Area &area : BWEM::Map::Instance().Areas()) {
		for (const BWEM::Base &base : area.Bases()) {
			availableBases_.push_back(&base);
		}
	}

	std::sort(availableBases_.begin(), availableBases_.end(), [&startPos](const BWEM::Base *a, const BWEM::Base *b) {
		return (a->Location().getDistance(startPos) < b->Location().getDistance(startPos));
	});
}
