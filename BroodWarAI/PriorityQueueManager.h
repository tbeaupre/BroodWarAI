#pragma once
#include<queue>
#include "BWAPI.h"
#include "BuildAction.h"

class CompareBuildActions {
	bool operator() (const BuildAction* lhs, const BuildAction* rhs) const
	{
		return (lhs->getPriorityLevel() < rhs->getPriorityLevel());
	}
};

class PriorityQueueManager {
public:
	static void Init();

	static void Push(BuildAction *buildAction);
	static BuildAction* Top();
	static void Pop();

private:
	static std::priority_queue<BuildAction*, std::vector<BuildAction*>, CompareBuildActions> priorityQueue_;
};
