#pragma once
#include "BWAPI.h"
#include "BuildAction.h"

class NolsyBase {
public:
	void Update();

	void OnCreateUnit(); // Called by UnitManager when a unit registered for create is create.
	void OnDestroyUnit(); // Called by UnitManager when a unit registered for destroy is destroyed.
	void OnMorphUnit(); // Called by UnitManager when a unit registered for morph changes UnitType.
	void OnCompleteUnit(); // Called by UnitManager when a unit registered for complete is completed.

	void SoftCancel(); // Postpones an action, but does not scrap it.
	void Resume(); // Resumes an action after it has been soft cancelled.
	void HardCancel(); // Tosses in the towel.

protected:
	enum Status {
		PAUSED, // Soft cancelled actions that may be resumed at some point.
		UNSTARTED, // Actions that haven't been started yet, or have just been restarted.
		STOPPABLE, // Actions in motion that don't require a cancel (eg a drone moving to expansion location).
		CANCELLABLE // Actions in motion that require a cancel input to cancel.
	};

	Status status_ = UNSTARTED; // See above.
	BWAPI::Unit unit_; // The worker expanding, unit being morphed, structure upgrading, etc.

	virtual void HandleUnstarted() = 0; // Attempts to start the task.
	virtual void HandleStoppable() { /* Optional! */ }; // Completes in-between steps like exploring build locations.
	virtual void HandleCancellable() { /* Optional! */ }; // Checks for complete conditions if necessary.
	virtual void Cancel() = 0; // Cancels action currently in progress, but won't give back workers, structures, etc.

	void Suicide(); // Ends it all.
};
