#pragma once
#include "Coordinate.h"

namespace console_maze {
namespace maze {

	uint8_t* generateWallConfigurations(int width, int height);
	int coordinateToIndex(common::Coordinate coords, common::Coordinate bounds);

} }