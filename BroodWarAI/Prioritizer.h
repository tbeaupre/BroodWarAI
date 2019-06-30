#pragma once
#include "BuildAction.h"
#include <vector>


class Prioritizer
{
public:
	static void FileRequest(std::vector<BuildAction*> action, int priority = 1);
};

