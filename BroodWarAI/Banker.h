#pragma once
static class Banker
{

private:
	BuildAction* GetNext();

public:
	void Update(int min, int gas, int supply, int larva = 0);
};

