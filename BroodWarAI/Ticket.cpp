#pragma once
#include "Ticket.h"
#include "BuildAction.h"
#include "Bill.h"


using namespace std;

BuildAction *actionList_;
Bill totalCost_;

Ticket::Ticket(BuildAction* x)
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
