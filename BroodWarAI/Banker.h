#pragma once
#include "Ticket.h"

class Banker
{

private:
	static Ticket *Peek();
	static Ticket *Pop();
	static bool Satisfiable(Ticket *toBuild, int min, int gas, int supply, int larva = 0);
	static void FireOffAFewNolsies();

public:
	static void Update(int min, int gas, int supply, int larva = 0);
	static void AddTicketToQueue(Ticket *ticket, int queue);
};




