#pragma once
#include "BuildOrders.h"

class BuildManager {
public:
	static void Init();
	static void OnFrame();

private:
	static BuildOrder build_;
	static int currentStep_;
	static const BuildAction *currentAction_;

	static void HandleAction();
	static void HandleUnitAction();
	static void HandleBuildingAction();
	static void HandleTechAction();
	static void HandleUpgradeAction();
	static void CompleteAction();
};