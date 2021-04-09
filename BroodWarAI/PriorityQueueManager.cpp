#include "PriorityQueueManager.h"

std::priority_queue<BuildAction*, std::vector<BuildAction*>, CompareBuildActions> priorityQueue_;

void PriorityQueueManager::Init() {}

void PriorityQueueManager::Push(BuildAction *buildAction) {
	priorityQueue_.push(buildAction);
}

BuildAction* PriorityQueueManager::Top() {
	return priorityQueue_.top();
}

void PriorityQueueManager::Pop() {
	priorityQueue_.pop();
}