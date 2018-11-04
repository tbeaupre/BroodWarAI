#include "BuildOrderStep.h"

BuildOrderStep::BuildOrderStep(BuildAction * newAction, int newRepeat) {
	condition = new BuildCondition();
	action = newAction;
	repeat = newRepeat;
}

BuildOrderStep::BuildOrderStep(BuildCondition *newCondition, BuildAction *newAction, int newRepeat) {
	condition = newCondition;
	action = newAction;
	repeat = newRepeat;
}

const BuildCondition *BuildOrderStep::getCondition() {
	return condition;
}

const BuildAction *BuildOrderStep::getAction() {
	return action;
}
