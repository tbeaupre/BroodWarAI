#pragma once
#include "BuildAction.h"
#include "NolsyBase.h"

class NolsyFactory
{
public:
	static NolsyBase createNolsy(BuildAction *action);
};