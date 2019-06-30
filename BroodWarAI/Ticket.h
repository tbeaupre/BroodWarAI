#pragma once
#include "BuildAction.h"
#include "Bill.h"
#include <vector>

/* Wrapper for BuildAction that stores a group of 1 or more build actions to be done in the order specified in the constructor. */
using namespace std;

class Ticket
{
public:
	Ticket(vector<BuildAction*> actionList);
	~Ticket();
	Bill getTotalCost();
	vector<BuildAction*> getActionList();
};
