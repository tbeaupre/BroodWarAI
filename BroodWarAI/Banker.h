#pragma once
#include<unordered_set>
#include "NolsyBase.h"
#include "BuildAction.h"

using namespace BWAPI;
using namespace BuildActionEnums;

class Banker {
public:
	static void OnFrame();
	static void CompleteAction(NolsyBase *nolsy);

private:
	static std::unordered_set<NolsyBase*> nolsies_;

	static bool AreRequirementsFulfilled(BuildAction* nextAction);
	static bool AreUnitRequirementsFulfilled(const UnitType *unitType);
	static bool AreTechRequirementsFulfilled(const TechType *techType);
	static bool AreUpgradeRequirementsFulfilled(const UpgradeType *upgradeType);
	static bool AreOtherRequirementsFulfilled(const OtherActionType otherType);
};