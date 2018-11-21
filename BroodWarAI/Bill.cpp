#include "Bill.h"


int minerals_;
int gas_;
int supply_;
int larva_;

Bill::Bill(int minerals, int gas, int supply, int larva) {
	minerals_ = minerals;
	gas_ = gas;
	supply_ = supply;
	larva_ = larva;
}

Bill::~Bill()
{
}
