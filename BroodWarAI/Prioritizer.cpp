#include "Prioritizer.h"
#include "Banker.h"

void Prioritizer::FileRequest(BuildAction *action, int priority)
{
	Ticket *incomingTicket = new Ticket(action);
	Banker::AddTicketToQueue(incomingTicket, priority);
}
