#pragma once
#include "Banker.h"
#include "Ticket.h"
#include "NolsyBase.h"
#include <iterator>
#include <queue>
#define QUEUE_COUNT 10

using namespace std;

static vector<queue<Ticket*>> queueArray_ = vector<queue<Ticket*>>(QUEUE_COUNT);
// pointer to the highest priority ticket
static Ticket *next_ = nullptr;
// when lock == true, no resources can be spent until the current ticket is out the door. If false, lower priority tickets can be fired.
static bool lock_ = false;


Ticket * Banker::Peek()
{
	for each (queue<Ticket*> queue in queueArray_)
	{
		if (size(queue) > 0) {
			return queue.front();
		}
	}
	return nullptr;
}

Ticket * Banker::Pop()
{
	int index = 0;
	for each (queue<Ticket*> queue in queueArray_)
	{
		if (size(queue) > 0) {
			Ticket *toReturn = queue.front();
			queue.pop();
			if (index == 0) lock_ = true;
			return toReturn;
		}
		index++;
	}
	return nullptr;
}

bool Banker::Satisfiable(Ticket *toBuild, int min, int gas, int supply, int larva)
{
	Bill toSatisfy = toBuild->getTotalCost();
	return (
		min >= toSatisfy.minerals &&
		gas >= toSatisfy.gas &&
		supply >= toSatisfy.supply &&
		larva >= toSatisfy.larva); // its yer boy larva
}

void Banker::FireOffANolsy()
{
	for each (BuildAction *action in next_ -> getActionList()) {
		
	}
}


void Banker::Update(int min, int gas, int supply, int larva)
{
	if (next_ == nullptr) {
		next_ = Pop();
	}
	if (Satisfiable(next_, min, gas, supply, larva)) {
		FireOffANolsy();
	}
	else {

	}
}

void Banker::AddTicketToQueue(Ticket *ticket, int priority)
{
	if (priority >= QUEUE_COUNT) priority = QUEUE_COUNT - 1; // if the priority is super low, add it to the last available queue. 
	queueArray_[priority].push(ticket);
}


