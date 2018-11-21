#include "Banker.h"
#include "Ticket.h"
#include <queue>
#define QUEUE_COUNT 10

using namespace std;

static vector<queue<Ticket*>> queueArray_ = vector<queue<Ticket*>>(QUEUE_COUNT);
static Ticket *next_;


Ticket *Banker::GetNext()
{
	for each (queue<Ticket*> queue in queueArray_)
	{
		if (queue.size > 0) {
			Ticket *toReturn = queue.front;
			queue.pop;
			return toReturn;
		}
	}
	return nullptr;
}

bool Banker::Satisfiable(Ticket *toBuild, int min, int gas, int supply, int larva)
{
	return false;
}

void Banker::FireOffANolsy()
{

}

void Banker::Update(int min, int gas, int supply, int larva)
{
	
}

void Banker::AddTicketToQueue(Ticket *ticket, int queue)
{
	if (queue >= QUEUE_COUNT) queue = QUEUE_COUNT-1;
	queueArray_[queue].push(ticket);
}


