#pragma once
#include "BuildAction.h"
#include "Bill.h"
#include <vector>

/*	Wrapper for BuildAction that stores a group of 1 or more build actions to be 
	done in the order specified in the constructor as well as a priority */

using namespace std;

class Ticket
{
public:
	Ticket(vector<BuildAction*> actionList, int priority);
	~Ticket();
	Bill *getTotalCost(); // returns a bill with the sum of every resource over every ticket
	vector<BuildAction*> getActionList(); // all the actions in the ticket
	int getPriority();
	void setPriority(int p);
};
