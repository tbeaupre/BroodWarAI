#include "Clarence.h"
#include <iostream>
#include "UnitManager.h"
#include "Debug.h"

using namespace BWAPI;
using namespace Filter;
//using namespace BWEM;
//using namespace BWEM::BWAPI_ext;
//using namespace BWEM::utils;

namespace { auto &theMap = BWEM::Map::Instance(); }

void Clarence::onStart() {
	try {
		// Hello World!
		Broodwar->sendText("Hello world!");

		// Print the map name.
		// BWAPI returns std::string when retrieving a string, don't forget to add .c_str() when printing!
		Broodwar << "The map is " << Broodwar->mapName() << "!" << std::endl;

		// Enable the UserInput flag, which allows us to control the bot and type messages.
		Broodwar->enableFlag(Flag::UserInput);

		// Uncomment the following line and the bot will know about everything through the fog of war (cheat).
		//Broodwar->enableFlag(Flag::CompleteMapInformation);

		// Set the command optimization level so that common commands can be grouped
		// and reduce the bot's APM (Actions Per Minute).
		Broodwar->setCommandOptimizationLevel(2);

		// Check if this is a replay
		if (Broodwar->isReplay()) {

			// Announce the players in the replay
			Broodwar << "The following players are in this replay:" << std::endl;

			// Iterate all the players in the game using a std:: iterator
			Playerset players = Broodwar->getPlayers();
			for (auto p : players) {
				// Only print the player if they are not an observer
				if (!p->isObserver())
					Broodwar << p->getName() << ", playing as " << p->getRace() << std::endl;
			}

		} else // if this is not a replay
		{
			UnitManager::Init();
			BuildManager::Init();
			BWAPI::Broodwar->setLocalSpeed(20);

			// Retrieve you and your enemy's races. enemy() will just return the first enemy.
			// If you wish to deal with multiple enemies then you must use enemies().
			if (Broodwar->enemy()) // First make sure there is an enemy
				Broodwar << "The matchup is " << Broodwar->self()->getRace() << " vs " << Broodwar->enemy()->getRace() << std::endl;

			Broodwar << "Map initialization..." << std::endl;

			theMap.Initialize();
			theMap.EnableAutomaticPathAnalysis();
			bool startingLocationsOK = theMap.FindBasesForStartingLocations();
			assert(startingLocationsOK);
			BaseManager::Init(Broodwar->self()->getStartLocation());
		}
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onEnd(bool isWinner) {
	// Called when the game ends
	try {
		if (isWinner) {
			// Log your win here!
		}
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onFrame() {
	// Called once every game frame
	try {
		BWEM::utils::drawMap(theMap);

		// Display the game frame rate as text in the upper left area of the screen
		Broodwar->drawTextScreen(200, 0, "FPS: %d", Broodwar->getFPS());
		Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS());
		auto counts = UnitManager::GetCounts();
		Broodwar->drawTextScreen(200, 40, "Larvae: %d   Workers: %d   Units: %d   Structures: %d", counts[0], counts[1], counts[2], counts[3]);
		Debug::OnFrame();

		// Return if the game is a replay or is paused
		if (Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self())
			return;

		// Prevent spamming by only running our onFrame once every number of latency frames.
		// Latency frames are the number of frames before commands are processed.
		if (Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0)
			return;

		BuildManager::OnFrame();

		// Iterate through all the units that we own
		for (auto &u : Broodwar->self()->getUnits()) {
			// Ignore the unit if it no longer exists
			// Make sure to include this block when handling any Unit pointer!
			if (!u->exists())
				continue;

			// Ignore the unit if it has one of the following status ailments
			if (u->isLockedDown() || u->isMaelstrommed() || u->isStasised())
				continue;

			// Ignore the unit if it is in one of the following states
			if (u->isLoaded() || !u->isPowered() || u->isStuck())
				continue;

			// Ignore the unit if it is incomplete or busy constructing
			if (!u->isCompleted() || u->isConstructing())
				continue;

			// If the unit is a worker unit
			if (u->getType().isWorker()) {
				// if our worker is idle
				if (u->isIdle()) {
					// Order workers carrying a resource to return them to the center,
					// otherwise find a mineral patch to harvest.
					if (u->isCarryingGas() || u->isCarryingMinerals()) {
						u->returnCargo();
					} else {
						if (!u->gather(u->getClosestUnit(IsMineralField || IsRefinery))) {
							// If the call fails, then print the last error message
							Broodwar << Broodwar->getLastError() << std::endl;
						}
					}
				} // closure: if idle
			}
		} // closure: unit iterator
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onSendText(std::string text) {
	try {
		BWEM::utils::MapDrawer::ProcessCommand(text);

		// Send the text to the game if it is not being processed.
		Broodwar->sendText("%s", text.c_str());


		// Make sure to use %s and pass the text as a parameter,
		// otherwise you may run into problems when you use the %(percent) character!
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onReceiveText(BWAPI::Player player, std::string text) {
	try {
		// Parse the received text
		Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onPlayerLeft(BWAPI::Player player) {
	try {
		// Interact verbally with the other players in the game by
		// announcing that the other player has left.
		Broodwar->sendText("Goodbye %s!", player->getName().c_str());
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onNukeDetect(BWAPI::Position target) {
	try {
		// Check if the target is a valid position
		if (target) {
			// if so, print the location of the nuclear strike target
			Broodwar << "Nuclear Launch Detected at " << target << std::endl;
		} else {
			// Otherwise, ask other players where the nuke is!
			Broodwar->sendText("Where's the nuke?");
		}

		// You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onUnitDiscover(BWAPI::Unit unit) {}

void Clarence::onUnitEvade(BWAPI::Unit unit) {}

void Clarence::onUnitShow(BWAPI::Unit unit) {}

void Clarence::onUnitHide(BWAPI::Unit unit) {}

void Clarence::onUnitCreate(BWAPI::Unit unit) {
	try {
		if (Broodwar->isReplay()) {
			// if we are in a replay, then we will print out the build order of the structures
			if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral()) {
				int seconds = Broodwar->getFrameCount() / 24;
				int minutes = seconds / 60;
				seconds %= 60;
				Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
			}
		}
		UnitManager::CreateUnit(unit);
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onUnitDestroy(BWAPI::Unit unit) {
	try {
		if (unit->getType().isMineralField()) theMap.OnMineralDestroyed(unit);
		else if (unit->getType().isSpecialBuilding()) theMap.OnStaticBuildingDestroyed(unit);
		UnitManager::DestroyUnit(unit);
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onUnitMorph(BWAPI::Unit unit) {
	try {
		if (Broodwar->isReplay()) {
			// if we are in a replay, then we will print out the build order of the structures
			if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral()) {
				int seconds = Broodwar->getFrameCount() / 24;
				int minutes = seconds / 60;
				seconds %= 60;
				Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
			}
		}
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onUnitRenegade(BWAPI::Unit unit) {}

void Clarence::onSaveGame(std::string gameName) {
	try {
		Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
	} catch (const std::exception &e) {
		Broodwar << "EXCEPTION: " << e.what() << std::endl;
	}
}

void Clarence::onUnitComplete(BWAPI::Unit unit) {
	UnitManager::CompleteUnit(unit);
}
