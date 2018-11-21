#pragma once
#include "BuildAction.h"
#include "Bill.h"

/* Wrapper for BuildAction that stores a group of 1 or more build actions to be done in the order specified in the constructor. */


class Ticket
{
public:
	Ticket(BuildAction* actionList);
	~Ticket();
protected:
	Bill getTotalCost();

private:
	
};
