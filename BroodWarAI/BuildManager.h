#pragma once
#include "BuildOrders.h"

class BuildManager {
public:
	BuildManager();

	void OnFrame();

private:
	BuildOrder build_;
	int currentStep_;
	const BuildAction *currentAction_ = nullptr;

	void HandleAction();
	void HandleUnitAction();
	void HandleBuildingAction();
	void HandleTechAction();
	void HandleUpgradeAction();
	void CompleteAction();
};