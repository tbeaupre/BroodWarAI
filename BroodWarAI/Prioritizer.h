#pragma once
#include "BuildAction.h"
#include <vector>


/*	This file might seem useless, but one day, it'll house an AI agent that makes decisions about how to prioritize build actions
For now, this method optionally takes a suggested priority, presumably dictated by the hard coded build orders */

class Prioritizer
{
public:
	static void FileRequest(std::vector<BuildAction*> action, int priority = 1); // TODO make this beefier and more sophisticated
};

