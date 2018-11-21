#pragma once
#include "BuildAction.h"
static class Prioritizer
{
public:
	void FileRequest(BuildAction *action, int priority = 1);
};

