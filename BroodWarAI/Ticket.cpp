#pragma once
#include "Ticket.h"
#include "BuildAction.h"
#include "Bill.h"
#include <vector>


using namespace std;

vector<BuildAction*> actionList_;
Bill totalCost_;

Ticket::Ticket(vector<BuildAction*> x)
{
	actionList_ = x;
}

Ticket::~Ticket()
{
}

Bill Ticket::getTotalCost()
{
	return totalCost_;
}

vector<BuildAction*> Ticket::getActionList() {
	return actionList_;
}