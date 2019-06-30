#pragma once
#include "NolsyStructure.h"
#include "NolsyUnit.h"
#include "NolsyOther.h"
#include "NolsyUpgrade.h"
#include "NolsyTech.h"
#include "BuildAction.h"
#include "NolsyBase.h"

static class NolsyFactory
{
public:
	NolsyBase* createNolsy(BuildAction *action);
};