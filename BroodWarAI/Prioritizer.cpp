#pragma once
#include "Prioritizer.h"
#include "Banker.h"
#include <vector>

void Prioritizer::FileRequest(std::vector<BuildAction*> actionList, int priority = 1)
{
	Ticket *incomingTicket = new Ticket(actionList, priority);
	Banker::AddTicketToQueue(incomingTicket, priority);
}
