#include "Bill.h"




Bill::Bill(int minerals, int gas, int supply, int larva) {
	this->minerals = minerals;
	this->gas = gas;
	this->supply = supply;
	this->larva = larva;
}

Bill::~Bill()
{
}
