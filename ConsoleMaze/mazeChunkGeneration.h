#pragma once
#include "Coordinate.h"
#include "MazeUnit.h"

namespace console_maze {
namespace maze {

	MazeUnit* generateWallConfigurations(int width, int height);
	int coordinateToIndex(common::Coordinate coords, common::Coordinate bounds);

} }