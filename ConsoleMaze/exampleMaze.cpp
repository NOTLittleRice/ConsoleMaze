#include <iostream>
#include "Wall.h"
#include "MazeUnit.h"
#include "Display.h"
#include "ExampleMaze.h"

namespace console_maze {
namespace example {

void emptyCenter()
{
	int width = 3, height = 3; // represent dimensions of maze
	char* mazeBuffer = (char*)malloc(maze::display::calcBufferGridSize(width, height));

	maze::MazeUnit h[] = {

		maze::MazeUnit(common::wall::LEFT_WALL | common::wall::TOP_WALL),
		maze::MazeUnit(common::wall::LEFT_WALL | common::wall::TOP_WALL),
		maze::MazeUnit(common::wall::LEFT_WALL | common::wall::TOP_WALL),

		maze::MazeUnit(common::wall::LEFT_WALL | common::wall::TOP_WALL),
		maze::MazeUnit(0),
		maze::MazeUnit(common::wall::TOP_WALL),

		maze::MazeUnit(common::wall::LEFT_WALL | common::wall::TOP_WALL),
		maze::MazeUnit(common::wall::LEFT_WALL),
		maze::MazeUnit(common::wall::LEFT_WALL | common::wall::TOP_WALL),
	};

	maze::display::populateBuffer(h, mazeBuffer, width, height);

	int bufferWidth = maze::display::calcBufferForWidth(width);
	char* rowBuffer = (char*)malloc(bufferWidth + 1);
	rowBuffer[bufferWidth] = '\0';
	std::cout << std::endl;

	int bufferHeight = maze::display::calcBufferForHeight(height);
	for (int row = 0; row < bufferHeight; row++)
	{
		strncpy_s(rowBuffer, bufferWidth + 1, mazeBuffer + (bufferWidth * row), bufferWidth);
		std::cout << rowBuffer << std::endl;
	}

	free(mazeBuffer);
	free(rowBuffer);
}

void S()
{
	int width = 2, height = 5; // represent dimensions of maze
	char* mazeBuffer = (char*)malloc(maze::display::calcBufferGridSize(width, height));

	maze::MazeUnit h[] = {

		maze::MazeUnit(common::wall::TOP_WALL | common::wall::LEFT_WALL),
		maze::MazeUnit(common::wall::TOP_WALL),

		maze::MazeUnit(common::wall::LEFT_WALL),
		maze::MazeUnit(common::wall::LEFT_WALL),

		maze::MazeUnit(common::wall::LEFT_WALL),
		maze::MazeUnit(common::wall::TOP_WALL),

		maze::MazeUnit(common::wall::TOP_WALL | common::wall::LEFT_WALL),
		maze::MazeUnit(common::wall::LEFT_WALL),

		maze::MazeUnit(common::wall::LEFT_WALL),
		maze::MazeUnit(0),

	};

	maze::display::populateBuffer(h, mazeBuffer, width, height);

	int bufferWidth = maze::display::calcBufferForWidth(width);
	char* rowBuffer = (char*)malloc(bufferWidth + 1);
	rowBuffer[bufferWidth] = '\0';
	std::cout << std::endl;

	int bufferHeight = maze::display::calcBufferForHeight(height);
	for (int row = 0; row < bufferHeight; row++)
	{
		strncpy_s(rowBuffer, bufferWidth + 1, mazeBuffer + (bufferWidth * row), bufferWidth);
		std::cout << rowBuffer << std::endl;
	}

	free(mazeBuffer);
	free(rowBuffer);
}

}
}