#pragma once
#include "globalVar.hpp" 			//!< NOTE: Cause multiple definition problems with piece.cpp file

#include <string>
#include <vector>

/**
 * @brief Process the file data and fetch the moves set for every piece.
 * @details The function follows the file structure to fetch the data.
 */
void getMoves();

