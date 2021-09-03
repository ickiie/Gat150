#include "FileSystem.h"
#include <filesystem>

void nc::SetFilePath(const std::string& pathname) {

	std::filesystem::current_path(pathname);
}

std::string nc::GetFilePath() {

	return std::filesystem::current_path().string();
}
