#include "BuildManager.h"
#include "NolsyUnit.h"

using namespace BuildActionEnums;

BuildOrder BuildManager::build_;
int BuildManager::currentStep_ = 0;
const BuildAction *BuildManager::currentAction_ = nullptr;
NolsyBase* BuildManager::nolsy_ = nullptr;

void BuildManager::Init() {
	BuildOrder overPool = BuildOrders::GetOverPool();
	BuildOrder h3SpireH5Hydra = BuildOrders::Get3BaseSpire5HatchHydra();
	overPool.insert(overPool.end(), h3SpireH5Hydra.begin(), h3SpireH5Hydra.end());

	build_ = overPool;
}

void BuildManager::OnFrame() {
	if (currentAction_ != nullptr) {
		BWAPI::Broodwar->drawTextScreen(50, 0, "Current Action: %s", currentAction_->PrintAction().c_str());
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
	if (nolsy_) {
		nolsy_->Update();
		return;
	}
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
	nolsy_ = new NolsyUnit(*currentAction_->getUnitType());
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
	BWAPI::Broodwar->drawTextScreen(50, 20, "Job's Done!");
	delete nolsy_;
	nolsy_ = nullptr;
	BuildOrderStep *step = build_[currentStep_];
	step->setComplete();
	if (step->isComplete()) {
		currentAction_ = nullptr;
		++currentStep_;
	}
}
