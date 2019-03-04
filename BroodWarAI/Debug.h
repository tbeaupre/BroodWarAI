#pragma once
#include "BWAPI.h"

struct DebugMessage {
	DebugMessage(std::string message, int duration);

	std::string message_;
	int duration_;

	void Print(int y);
};

class Debug {
public:
	static void OnFrame();
	static void AddMessage(int key, std::string message, int duration = 200);

private:
	static std::map<int, DebugMessage> messages_;
};
