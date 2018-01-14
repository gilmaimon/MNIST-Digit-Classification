#pragma once
#include <string>

struct BackupAble {
	virtual void SaveToFile(std::string filename) = 0;
	virtual void LoadFromFile(std::string filename) = 0;
	virtual ~BackupAble() = default;
};

