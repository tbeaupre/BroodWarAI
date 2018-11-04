#pragma once
#include "BuildCondition.h"
#include "BuildAction.h"

class BuildOrderStep {
public:
	BuildOrderStep(BuildAction *newAction, int repeat = 1);
	BuildOrderStep(BuildCondition *newCondition, BuildAction *newAction, int repeat = 1);

	const BuildCondition *getCondition() const { return condition_; }
	const BuildAction *getAction() const { return action_; }
	bool isComplete() const { return isComplete_; }

	void setComplete();

private:
	const BuildCondition *condition_;
	const BuildAction *action_;
	int repeat_;
	bool isComplete_;
};
