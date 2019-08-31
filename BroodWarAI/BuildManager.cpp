#include "BuildManager.h"
#include "NolsyFactory.h"

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
	build_ = BuildOrders::GetTest();
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
	nolsy_ = NolsyFactory::BuildNolsy(currentAction_);
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
