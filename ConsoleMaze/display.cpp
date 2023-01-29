#pragma once
#include "Display.h"
#include "MazeChunk.h"
#include "MazeUnit.h"
#include "MazeChunkGeneration.h"
#include "Wall.h"
#include "Coordinate.h"

namespace console_maze {
namespace maze {
namespace display {


// width and height describe dimensions of the maze
// assumes the buffer correlates to the maze's dimensions where
// maze_width * 2 + 1 matches width
// maze_height * 2 + 1 matches height
void populateBuffer(maze::MazeUnit* maze, char* buffer, int width, int height)
{
	int rowPixelWidth = calcBufferForWidth(width);
	char cornerChar = '+';
	char wallChar = '|';
	char floorChar = '-';
	char unoccupiedChar = ' ';
	char centerChar = ' ';

	for (int i = 0; i < height; i++) // y dimension within maze
	{
		for (int j = 0; j < width; j++) // x dimension within maze
		{
			auto walls = (maze + i * width + j)->GetWalls();
			char charUsed = ' ';
			int topLeftCorner =
				UNIT_WIDTH_IN_BUFFER * j + // shift based on x dimension within maze
				UNIT_HEIGHT_IN_BUFFER * i * rowPixelWidth;// shift based on y dimension within maze

			buffer[topLeftCorner] = cornerChar; // top left corner of square
			buffer[topLeftCorner + UNIT_WIDTH_IN_BUFFER] = cornerChar; // top right corner of square
			buffer[topLeftCorner + UNIT_HEIGHT_IN_BUFFER * rowPixelWidth] = cornerChar; // bottom left corner of square
			buffer[topLeftCorner + UNIT_HEIGHT_IN_BUFFER * rowPixelWidth + UNIT_WIDTH_IN_BUFFER] = cornerChar; // bottom right corner of square

			if (((walls & common::wall::LEFT_WALL) >> common::wall::LEFT_WALL_BIT) % 2)
			{
				charUsed = wallChar;
			}
			else
			{
				charUsed = unoccupiedChar;
			}
			for (int i = 1; i < UNIT_HEIGHT_IN_BUFFER; i++)
			{
				buffer[topLeftCorner + rowPixelWidth * i] = charUsed;
			}

			if (((walls & common::wall::TOP_WALL) >> common::wall::TOP_WALL_BIT) % 2)
			{
				charUsed = floorChar;
			}
			else {
				charUsed = unoccupiedChar;
			}
			for (int i = 1; i < UNIT_WIDTH_IN_BUFFER; i++)
			{
				buffer[topLeftCorner + i] = charUsed;
			}

			//fill in center
			for (int x = 1; x < UNIT_WIDTH_IN_BUFFER; x++)
			{
				for (int y = 1; y < UNIT_HEIGHT_IN_BUFFER; y++)
					buffer[topLeftCorner + rowPixelWidth * y + x] = centerChar;
			}
		}
	}
}

int calcBufferForWidth(int width)
{
	return width * UNIT_WIDTH_IN_BUFFER + 1;
}

int calcBufferForHeight(int height)
{
	return height * UNIT_HEIGHT_IN_BUFFER + 1;
}

int calcBufferGridSize(int width, int height)
{
	return calcBufferForWidth(width) * calcBufferForHeight(height);
}

void LoadConfiguration(int width, int height, uint8_t* wallConfiguration)
{
	//int width = 2, height = 5; // represent dimensions of maze
	char* mazeBuffer = (char*)malloc(calcBufferGridSize(width, height));

	maze::MazeUnit* h = (maze::MazeUnit*)malloc(sizeof(maze::MazeUnit) * width * height);

	if (h == nullptr)
	{
		throw;
	}

	auto bounds = common::Coordinate{ width, height };
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			auto coords = common::Coordinate{ x, y };
			int location = maze::coordinateToIndex(coords, bounds);
			h[location] = maze::MazeUnit(wallConfiguration[location]);
		}
	}

	populateBuffer(h, mazeBuffer, width, height);

	int bufferWidth = calcBufferForWidth(width);
	char* rowBuffer = (char*)malloc(bufferWidth + 1);
	rowBuffer[bufferWidth] = '\0';
	std::cout << std::endl;

	int bufferHeight = calcBufferForHeight(height);
	for (int row = 0; row < bufferHeight; row++)
	{
		strncpy_s(rowBuffer, bufferWidth + 1, mazeBuffer + (bufferWidth * row), bufferWidth);
		std::cout << rowBuffer << std::endl;
	}

	free(mazeBuffer);
	free(rowBuffer);
}

} } }