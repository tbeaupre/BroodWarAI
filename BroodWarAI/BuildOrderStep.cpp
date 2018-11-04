#include "BuildOrderStep.h"

BuildOrderStep::BuildOrderStep(BuildAction *action, int repeat) {
	condition_ = new BuildCondition();
	action_ = action;
	repeat_ = repeat;
}

BuildOrderStep::BuildOrderStep(BuildCondition *condition, BuildAction *action, int repeat) {
	condition_ = condition;
	action_ = action;
	repeat_ = repeat;
}

void BuildOrderStep::setComplete() {
	--repeat_;
	if (repeat_ == 0) {
		isComplete_ = true;
	}
}
