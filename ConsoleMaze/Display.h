#pragma once
#include "MazeUnit.h"
#include "MazeChunk.h"
#include "Coordinate.h"
#include "CharBuffer.h"

namespace console_maze {
namespace maze {
namespace display {

enum MAZE_UNIT_SIZE_IN_BUFFER
{
	UNIT_WIDTH_IN_BUFFER = 5,
	UNIT_HEIGHT_IN_BUFFER = 4
};

int calcBufferForWidth(int width);
int calcBufferForHeight(int height);
int calcBufferGridSize(int width, int height);
void populateBuffer(maze::MazeUnit* maze, char* buffer, int width, int height);
void LoadConfiguration(int width, int height, MazeUnit* wallConfiguration);

void loadToBuffer(const MazeChunk maze, common::Coordinate center, char* buffer, common::Coordinate bufferSize);
void loadToBuffer(const MazeChunk maze, common::Coordinate center, CharBuffer buffer);

} } }