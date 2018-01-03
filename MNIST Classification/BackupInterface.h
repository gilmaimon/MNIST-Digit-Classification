#pragma once
#include <string>

struct IBackup {
	virtual void SaveToFile(std::string filename) = 0;
	virtual void LoadFromFile(std::string filename) = 0;
	virtual ~IBackup() = default;
};

