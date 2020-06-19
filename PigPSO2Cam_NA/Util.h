#pragma once
#include <string>
#include <fstream>
#include <vector>

std::string getLastLine(std::ifstream& in);
uintptr_t readPointerOffset(uintptr_t ptr, std::vector<unsigned int> offsets, bool offsetBase=false);