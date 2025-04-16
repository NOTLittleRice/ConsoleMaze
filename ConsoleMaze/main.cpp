#include <iostream>
#include "Display.h"
#include "MazeChunkGeneration.h"
#include "ExampleMaze.h"

int main()
{
	console_maze::example::emptyCenter();
	console_maze::example::S();

	int width = 30;
	int height = 9;
	console_maze::maze::MazeUnit* wallConfiguration = console_maze::maze::generateWallConfigurations(width, height);
	console_maze::maze::display::LoadConfiguration(width, height, wallConfiguration);

	return 0;
}