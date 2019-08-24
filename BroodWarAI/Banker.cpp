#pragma once
#include "Banker.h"
#include "Ticket.h"
#include "NolsyBase.h"
#include "NolsyFactory.h"
#include <iterator>
#include <queue>
#define QUEUE_COUNT 10

using namespace std;
using namespace BWAPI;

vector<queue<Ticket*>> queueArray_;
/* pointer to the highest priority ticket */
Ticket *next_;
/*	If lock == true, no resources can be spent until the current ticket is out the door. 
	If false, lower priority tickets can be fired. */
bool lock_;
NolsyFactory nolsyFactory;

void Banker::Init() {
	lock_ = false;
	next_ = nullptr;
	queueArray_ = vector<queue<Ticket*>>(QUEUE_COUNT);
}

Ticket * Banker::Peek()
{
	int i = 0;
	while (size(queueArray_[i]) == 0) {
		i++;
		if (i == QUEUE_COUNT) return nullptr; // no tickets currently filed
	}

	return queueArray_[i].front(); // return the first ticket in the highest non-empty priority array
}

Ticket * Banker::Pop()
{
	int i = 0;
	while (size(queueArray_[i]) == 0) {
		i++;
		if (i == QUEUE_COUNT) return nullptr; // no tickets currently filed
	}
	Ticket *toReturn = queueArray_[i].front();
	queueArray_[i].pop();
	if (i == 0) lock_ = true; // highest priority array locks
	return toReturn; // return the first ticket in the highest non-empty priority array
}

// returns whether a bill can be satisfied by current funds. Maybe move this function out at some point?
bool Banker::Satisfiable(Ticket *toBuild, Bill *funds)
{
	Bill* toSatisfy = toBuild->getTotalCost();
	return (
		funds->minerals >= toSatisfy->minerals &&
		funds->gas >= toSatisfy->gas &&
		funds->supply >= toSatisfy->supply &&
		funds->larva >= toSatisfy->larva); // its yer boy larva
}

void Banker::FireOffAFewNolsies()
{
	for each (BuildAction *action in next_ -> getActionList()) {
		NolsyBase* toFire = nolsyFactory.createNolsy(action);
	}
}

void Banker::Update(Bill *funds)
{
	if (next_ == nullptr) {
		next_ = Pop();
	}
	else if (Satisfiable(next_, funds)) {
		FireOffAFewNolsies();
	}
	else {
		Broodwar << "pass the doobskin mate, theres fuckin nothin left to do cunt." << std::endl;
	}
}

void Banker::AddTicketToQueue(Ticket *ticket)
{
	if (ticket->getPriority() >= QUEUE_COUNT) ticket->setPriority(QUEUE_COUNT - 1); // if the priority is super low, add it to the last available queue. 
	queueArray_[ticket->getPriority()].push(ticket);
}
