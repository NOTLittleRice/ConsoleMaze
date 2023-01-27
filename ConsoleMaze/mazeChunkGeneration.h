#pragma once

struct Coordinate
{
	int x, y;
};

uint8_t* generateWallConfigurations(int width, int height);
int coordinateToIndex(Coordinate coords, Coordinate bounds);