#include "Bill.h"

Bill::Bill(int minerals, int gas, int supply, int larva) {
	this->minerals = minerals;
	this->gas = gas;
	this->supply = supply;
	this->larva = larva;
}


Bill* Bill::operator+(Bill *b) {
	return new Bill(
		this->minerals + b->minerals,
		this->gas + b->gas,
		this->supply + b->supply,
		this->larva + b->larva);
}


Bill* Bill::operator-(Bill *b) {
	return new Bill(
		this->minerals - b->minerals,
		this->gas - b->gas,
		this->supply - b->supply,
		this->larva - b->larva);
}

Bill::~Bill()
{
}
