#pragma once
class Bill
{
public:
	Bill(int minerals = 0, int gas = 0, int supply = 0, int larva = 0);
	Bill* operator+(Bill* b);
	Bill * operator-(Bill* b);
	~Bill();
	int minerals;
	int gas;
	int supply;
	int larva;
};
