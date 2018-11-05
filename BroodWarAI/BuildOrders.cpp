#include "BWAPI.h"
#include "BuildOrders.h"

BuildOrder BuildOrders::GetOverPool() {
	return BuildOrder({
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Drone),
			5),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Overlord)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Spawning_Pool)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Spawning_Pool, 1),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Drone),
			3),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Zergling),
			3),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Hatchery)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Hatchery, 2),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Hatchery)),
	});
}

BuildOrder BuildOrders::Get3BaseSpire5HatchHydra() {
	return BuildOrder({
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Hatchery, 3),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Extractor)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Lair)),
		new BuildOrderStep(
			new BuildCondition(ResourceType::GAS, 100),
			new BuildAction(&BWAPI::UpgradeTypes::Metabolic_Boost)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Lair, 1, true),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Spire)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Spire, 1),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Hatchery)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Hatchery, 3),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Extractor)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Extractor, 2),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Hydralisk_Den)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Hydralisk_Den, 1),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Hatchery)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UpgradeTypes::Muscular_Augments)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UpgradeTypes::Pneumatized_Carapace)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Evolution_Chamber)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Scourge),
			2),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UpgradeTypes::Zerg_Missile_Attacks)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Creep_Colony),
			2),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Creep_Colony, 2),
			new BuildAction(&BWAPI::UpgradeTypes::Grooved_Spines)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Extractor)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Extractor, 3),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Drone),
			5),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Mutalisk),
			9),
		new BuildOrderStep(
			new BuildAction(&BWAPI::TechTypes::Lurker_Aspect)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Evolution_Chamber)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Evolution_Chamber, 2),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Evolution_Chamber)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Evolution_Chamber, 3),
			new BuildAction(&BWAPI::UnitTypes::Zerg_Hatchery)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Hatchery, 5),
			new BuildAction(&BWAPI::UpgradeTypes::Zerg_Missile_Attacks)),
		new BuildOrderStep(
			new BuildAction(&BWAPI::UnitTypes::Zerg_Drone),
			9),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Evolution_Chamber, 2, true),
			new BuildAction(&BWAPI::UpgradeTypes::Zerg_Carapace)),
		new BuildOrderStep(
			new BuildCondition(&BWAPI::UnitTypes::Zerg_Evolution_Chamber, 3, true),
			new BuildAction(&BWAPI::UpgradeTypes::Zerg_Melee_Attacks))
	});
}
