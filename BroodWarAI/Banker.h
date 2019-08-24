#pragma once
#include "Ticket.h"

class Banker
{

private:
	Ticket *Peek();
	Ticket *Pop();
	static bool Satisfiable(Ticket *toBuild, Bill * funds);
	void FireOffAFewNolsies();
	

public:
	void Init();
	void Update(Bill * funds);
	void AddTicketToQueue(Ticket *ticket);
};




