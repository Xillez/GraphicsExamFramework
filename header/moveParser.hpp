#pragma once

#include <string>
#include <vector>

std::vector<std::pair<int, int>> parseMoveList(std::vector<std::string> moveList);

std::pair<int, int> parseMove(std::string move);