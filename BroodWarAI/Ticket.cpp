#pragma once
#include "Ticket.h"
#include "BuildAction.h"
#include "Bill.h"
#include <vector>


using namespace std;

vector<BuildAction*> actionList_;
Bill *totalCost_;
int priority_;

Ticket::Ticket(vector<BuildAction*> actionList, int priority)
{
	actionList_ = actionList;
	priority_ = priority;
	totalCost_ = nullptr;

}

Ticket::~Ticket()
{
}

Bill *Ticket::getTotalCost()
{
	if (totalCost_ != nullptr) return totalCost_;
	totalCost_ = new Bill;
	for each (BuildAction* action in actionList_) {
		totalCost_ += action->getBill();
	}
}

vector<BuildAction*> Ticket::getActionList() {
	return actionList_;
}

int Ticket::getPriority()
{
	return priority_;
}

void Ticket::setPriority(int p)
{
	priority_ = p;
}

