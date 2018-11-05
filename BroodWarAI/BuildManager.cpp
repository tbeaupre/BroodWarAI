#include "BuildManager.h"

BuildManager::BuildManager() {
	BuildOrder overPool = BuildOrders::GetOverPool();
	BuildOrder h3SpireH5Hydra = BuildOrders::Get3BaseSpire5HatchHydra();
	overPool.insert(overPool.end(), h3SpireH5Hydra.begin(), h3SpireH5Hydra.end());

	build_ = overPool;
	currentStep_ = 0;
}

void BuildManager::OnFrame() {
	if (currentAction_ != nullptr) {
		HandleAction();
	} else {
		// Start a new action.
		if (currentStep_ == build_.size())
			return; // We're done with the build.

		BuildOrderStep *step = build_[currentStep_];

		if (step->getCondition()->IsConditionMet()) {
			// The condition is met so start on the action for this build step.
			currentAction_ = step->getAction();
			HandleAction();
		}
	}
}

void BuildManager::HandleAction() {
	currentAction_->PrintAction();
	switch (currentAction_->getType()) {
		case ActionType::UNIT:
			if (currentAction_->isBuilding()) {
				HandleBuildingAction();
			} else {
				HandleUnitAction();
			}
			break;
		case ActionType::TECH:
			HandleTechAction();
			break;
		case ActionType::UPGRADE:
			HandleUpgradeAction();
			break;
	}
}

void BuildManager::HandleUnitAction() {
	BWAPI::Unitset larvaSet = BWAPI::Broodwar->self()->getUnits().getLarva();
	auto larvaIter = larvaSet.begin();
	if (larvaIter != larvaSet.end()) {
		// There are some larva to choose from.
		BWAPI::Unit larva = *larvaIter;
		if (larva->exists()) {
			if (larva->morph(*currentAction_->getUnitType())) {
				CompleteAction();
			}
		}
	}
}

void BuildManager::HandleBuildingAction() {
	BWAPI::UnitType toBuild = *currentAction_->getUnitType();
	BWAPI::Unit builder = BWAPI::Broodwar->self()->getUnits().getClosestUnit(BWAPI::Filter::GetType == toBuild.whatBuilds().first &&
		(BWAPI::Filter::IsIdle || BWAPI::Filter::IsGatheringMinerals) &&
		BWAPI::Filter::IsOwned);
	if (builder) {
		if (toBuild == BWAPI::UnitTypes::Zerg_Creep_Colony) {
			BWAPI::TilePosition targetBuildLocation = BWAPI::Broodwar->getBuildLocation(toBuild, builder->getTilePosition(), 64, true); // This is different for Creep Colonies
			if (targetBuildLocation) {
				if (builder->build(toBuild, targetBuildLocation)) {
					CompleteAction(); // TODO: This should not be considered completion.
				}
			}
		}
		if (toBuild == BWAPI::UnitTypes::Zerg_Lair || toBuild == BWAPI::UnitTypes::Zerg_Hive) {
			BWAPI::Broodwar << "BUILDING A LAIR/HIVE" << std::endl;
			if (builder->build(toBuild)) {
				CompleteAction(); // TODO: This should not be considered completion.
			}
		}
		BWAPI::TilePosition targetBuildLocation = BWAPI::Broodwar->getBuildLocation(toBuild, builder->getTilePosition());
		if (targetBuildLocation) {
			if (builder->build(toBuild, targetBuildLocation)) {
				CompleteAction(); // TODO: This should not be considered completion.
			}
		}
	}
}

void BuildManager::HandleTechAction() {
	BWAPI::TechType toResearch = *currentAction_->getTechType();
	BWAPI::Unit researcher = BWAPI::Broodwar->self()->getUnits().getClosestUnit(BWAPI::Filter::GetType == toResearch.whatResearches() &&
		BWAPI::Filter::IsIdle &&
		BWAPI::Filter::IsOwned);
	if (researcher) {
		if (researcher->research(toResearch)) {
			CompleteAction();
		}
	}
}

void BuildManager::HandleUpgradeAction() {
	BWAPI::UpgradeType toUpgrade = *currentAction_->getUpgradeType();

	if (BWAPI::Broodwar->self()->isUpgrading(toUpgrade)) {
		CompleteAction();
	}

	BWAPI::Unit researcher = BWAPI::Broodwar->self()->getUnits().getClosestUnit(BWAPI::Filter::GetType == toUpgrade.whatUpgrades() &&
		BWAPI::Filter::IsIdle &&
		BWAPI::Filter::IsOwned);
	if (researcher) {
		researcher->upgrade(toUpgrade);
	}
}

void BuildManager::CompleteAction() {
	BWAPI::Broodwar << "Action Completed ";
	currentAction_->PrintAction();

	BuildOrderStep *step = build_[currentStep_];
	step->setComplete();
	if (step->isComplete()) {
		BWAPI::Broodwar << "Moving to Next Build Step" << std::endl;
		currentAction_ = nullptr;
		++currentStep_;
	}
}
