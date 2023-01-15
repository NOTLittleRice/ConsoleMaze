#include <iostream>
#include <time.h>
#include "Wall.h"
#include "mazeChunkGeneration.h"

// The grid is represented by a 1D array where the rows are stored in sequential order of one another

/// <summary>
/// 
/// </summary>
/// <param name="coords"></param>
/// <param name="bounds"></param>
/// <returns></returns>
int coordinateToIndex(Coordinate coords, Coordinate bounds)
{
	return coords.y * bounds.x + coords.x;
}

void branch(uint8_t* wallSet, Coordinate coords, Coordinate bounds, bool* usedSquares, int linkIdentifier);
bool inBounds(Coordinate coords, Coordinate bounds);
void processLink(uint8_t* wallSet, int linkIdentifier, Coordinate bounds);
void processVerticalLink(uint8_t* wallSet, int linkIdentifier, Coordinate bounds);
void processHorizontalLink(uint8_t* wallSet, int linkIdentifier, Coordinate bounds);
int countVerticalLinks(Coordinate bounds);
int countHorizontalLinks(Coordinate bounds);
int findBottomLink(Coordinate coords, Coordinate bounds);
int findRightLink(Coordinate coords, Coordinate bounds);
int findTopLink(Coordinate coords, Coordinate bounds);
int findLeftLink(Coordinate coords, Coordinate bounds);

uint8_t* generateWallConfigurations(int width, int height)
{
	// set aside memory appropriate for a width x height amount
	uint8_t* wallSet = (uint8_t*)malloc(sizeof(uint8_t) * width * height);
	// store whether or not the current maze square has been selected
	bool* usedSquares = (bool*)malloc(sizeof(bool) * width * height);

	// do more work later to check for when generation fails
	if (wallSet == nullptr)
	{
		throw;
	}
	if (usedSquares == nullptr)
	{
		throw;
	}

	Coordinate bounds = Coordinate{ width, height };
	// coordinate to begin maze generation from
	Coordinate startingCoord = Coordinate{ 0, 0 };
	
	for (int y = 0; y < bounds.y; y++)
	{
		for (int x = 0; x < bounds.x; x++)
		{
			Coordinate coords = Coordinate{ x, y };
			int location = coordinateToIndex(coords, bounds);
			// each unit in maze starts out as completely walled
			wallSet[location] = EVERY_WALL;
			usedSquares[location] = false;
			std::cout << (char)('A' + wallSet[location]) << std::endl;

		}
	}

	branch(wallSet, startingCoord, bounds, usedSquares, -1);

	return wallSet;
}

void branch(uint8_t* wallSet, Coordinate coords, Coordinate bounds, bool* usedSquares, int linkIdentifier)
{
	int location = coordinateToIndex(coords, bounds);
	if (!inBounds(coords, bounds) || usedSquares[location]) {
		return;
	}
	
	usedSquares[location] = true;
	processLink(wallSet, linkIdentifier, bounds);

	uint8_t branchOrder[] = { 0, 1, 2, 3 };
	int numPaths = 4;

	srand(time(NULL) * ((coords.x + 11) * (coords.y + 71) * 89) % 101); // seeding
	for (int toSwap = 0; toSwap < numPaths - 1; toSwap++)
	{
		int range = numPaths - toSwap; // amount that toSwap can be increased by
		int swapWith = rand() % range;

		uint8_t temp = branchOrder[toSwap];
		branchOrder[toSwap] = branchOrder[swapWith];
		branchOrder[swapWith] = temp;
	}

	for (int i = 0; i < 4; i++)
	{
		switch (branchOrder[i])
		{
		case 0:
			branch(wallSet, Coordinate{ coords.x + 1 , coords.y }, bounds, usedSquares, findRightLink(coords, bounds));
			break;
		case 1:
			branch(wallSet, Coordinate{ coords.x - 1 , coords.y }, bounds, usedSquares, findLeftLink(coords, bounds));
			break;
		case 2:
			branch(wallSet, Coordinate{ coords.x , coords.y + 1 }, bounds, usedSquares, findBottomLink(coords, bounds));
			break;
		case 3:
			branch(wallSet, Coordinate{ coords.x , coords.y - 1 }, bounds, usedSquares, findTopLink(coords, bounds));
			break;
		}
	}

	//int testX = 4;
	//int testY = 1;
	
	//branch(wallSet, Coordinate{ coords.x + 1 , coords.y }, bounds, usedSquares, testX * bounds.y + testY);
	//branch(wallSet, Coordinate{ coords.x - 1 , coords.y }, bounds, usedSquares, 0);
	//branch(wallSet, Coordinate{ coords.x , coords.y + 1 }, bounds, usedSquares, testX * bounds.y + testY);
	//branch(wallSet, Coordinate{ coords.x , coords.y - 1 }, bounds, usedSquares, 0);
	
	////branch(wallSet, Coordinate{ coords.x + 1 , coords.y }, bounds, usedSquares, findRightLink(coords, bounds));
	////branch(wallSet, Coordinate{ coords.x , coords.y + 1 }, bounds, usedSquares, findBottomLink(coords, bounds));

	//branch(wallSet, Coordinate{ coords.x , coords.y + 1 }, bounds, usedSquares, findRightLink(coords, bounds));
	//branch(wallSet, Coordinate{ coords.x + 1 , coords.y }, bounds, usedSquares, findRightLink(coords, bounds));
	

	
	return;
}

bool inBounds(Coordinate coords, Coordinate bounds)
{
	return
		(coords.x < bounds.x && coords.x >= 0) &&
		(coords.y < bounds.y && coords.y >= 0);
}

int countVerticalLinks(Coordinate bounds)
{
	return (bounds.y - 1) * bounds.x;
}

int countHorizontalLinks(Coordinate bounds)
{
	return (bounds.x - 1) * bounds.y;
}

void processLink(uint8_t* wallSet, int linkIdentifier, Coordinate bounds)
{
	int numVerticalLinks = countVerticalLinks(bounds);
	int numHorizontalLinks = countHorizontalLinks(bounds);
	
	if (linkIdentifier >= numHorizontalLinks)
	{
		processVerticalLink(wallSet, linkIdentifier, bounds);
	}
	else
	{
		processHorizontalLink(wallSet, linkIdentifier, bounds);
	}
}

void processVerticalLink(uint8_t* wallSet, int linkIdentifier, Coordinate bounds)
{
	int verticalLinkInd = linkIdentifier - countHorizontalLinks(bounds);

	int x = verticalLinkInd % bounds.x; // finding floored quotient of id and the number of columns in the grid
	int y = verticalLinkInd / bounds.x; // finding remainder of id and number of columns in the grid

	// find coordinate of square on top
	auto top = Coordinate{ x, y };
	// find coordinate of square on bottom
	auto btm = Coordinate{ x, y + 1 };

	int topLoc = coordinateToIndex(top, bounds);
	int btmLoc = coordinateToIndex(btm, bounds);

	wallSet[topLoc] = wallSet[topLoc] & compl BOTTOM_WALL;
	wallSet[btmLoc] = wallSet[btmLoc] & compl TOP_WALL;
}

void processHorizontalLink(uint8_t* wallSet, int linkIdentifier, Coordinate bounds)
{
	int horizontalLinkInd = linkIdentifier;

	int x = horizontalLinkInd / bounds.y; // finding floored quotient of id and the number of rows in the grid
	int y = horizontalLinkInd % bounds.y; // finding remainder of id and number of rows in the grid

	// find coordinate of square to left
	auto left = Coordinate{ x, y };
	// find coordinate of square to right
	auto right = Coordinate{ x + 1, y };

	int leftLoc = coordinateToIndex(left, bounds);
	int rightLoc = coordinateToIndex(right, bounds);

	// open right wall on wall to left of link
	wallSet[leftLoc] = wallSet[leftLoc] & compl RIGHT_WALL;
	// open left wall on wall to right of link
	wallSet[rightLoc] = wallSet[rightLoc] & compl LEFT_WALL;
}

/// <summary>
/// Finds link to the bottom of a given coord
/// </summary>
/// <param name="coords"></param>
/// <param name="bounds"></param>
/// <returns></returns>
int findBottomLink(Coordinate coords, Coordinate bounds)
{
	return coords.y * bounds.x + coords.x + countHorizontalLinks(bounds);
}

/// <summary>
/// Finds link to the right of a given coord
/// </summary>
/// <param name="coords"></param>
/// <param name="bounds"></param>
/// <returns></returns>
int findRightLink(Coordinate coords, Coordinate bounds)
{
	return coords.x * bounds.y + coords.y;
}

int findTopLink(Coordinate coords, Coordinate bounds)
{
	return (coords.y - 1) * bounds.x + coords.x + countHorizontalLinks(bounds);
}

int findLeftLink(Coordinate coords, Coordinate bounds)
{
	return (coords.x - 1) * bounds.y + coords.y;
}