#pragma once
#include "BuildCondition.h"
#include "BuildAction.h"

class BuildOrderStep {
public:
	BuildOrderStep(BuildAction *newAction, int newRepeat = 1);
	BuildOrderStep(BuildCondition *newCondition, BuildAction *newAction, int newRepeat = 1);

	const BuildCondition *getCondition();
	const BuildAction *getAction();

private:
	BuildCondition *condition;
	BuildAction *action;
	int repeat;
};
