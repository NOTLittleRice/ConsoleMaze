#pragma once
#include "MazeUnit.h"

namespace console_maze {
namespace maze {
namespace display {

enum MAZE_UNIT_SIZE_IN_BUFFER
{
	UNIT_WIDTH_IN_BUFFER = 6,
	UNIT_HEIGHT_IN_BUFFER = 4
};

int calcBufferForWidth(int width);
int calcBufferForHeight(int height);
int calcBufferGridSize(int width, int height);
void populateBuffer(maze::MazeUnit* maze, char* buffer, int width, int height);
void LoadConfiguration(int width, int height, uint8_t* wallConfiguration);

} } }