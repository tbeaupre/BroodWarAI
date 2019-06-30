#pragma once
#include "Prioritizer.h"
#include "Banker.h"
#include <vector>

void Prioritizer::FileRequest(std::vector<BuildAction*> action, int priority)
{
	Ticket *incomingTicket = new Ticket(action);
	Banker::AddTicketToQueue(incomingTicket, priority);
}
