#include "Banker.h"
#include "BuildAction.h"
#include <queue>

using namespace std;

static vector<queue<BuildAction*>> QueueArray;

BuildAction* Banker::GetNext()
{
	return;
}

void Banker::Update(int min, int gas, int supply, int larva)
{
	for each (queue<BuildAction*> var in QueueArray)
	{

	}
}
