#pragma once
#include "BuildOrders.h"
#include "NolsyBase.h"

class BuildManager {
public:
	static void Init();
	static void OnFrame();
	static void CompleteAction();

private:
	static BuildOrder build_;
	static int currentStep_;
	static const BuildAction *currentAction_;
	static NolsyBase *nolsy_;

	static void HandleAction();
};