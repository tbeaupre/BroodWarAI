#include "Debug.h"

using namespace BWAPI;

std::map<int, DebugMessage> Debug::messages_;

void Debug::OnFrame() {
	int y = 0;
	for (auto iter = messages_.begin(); iter != messages_.end(); iter++, y += 20) {
		if (iter->second.duration_ == 0) {
			messages_.erase(iter);
			y -= 20; // So this screen location may be used by the next message.
		} else {
			iter->second.Print(y);
			iter->second.duration_--;
		}
	}
}

void Debug::AddMessage(int key, std::string message, int duration) {
	messages_.insert_or_assign(key, DebugMessage(message, duration));
}

DebugMessage::DebugMessage(std::string message, int duration) {
	message_ = message;
	duration_ = duration;
}

void DebugMessage::Print(int y) {
	Broodwar->drawTextScreen(0, y, message_.c_str());
}
