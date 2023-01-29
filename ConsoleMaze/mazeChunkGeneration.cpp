#include <iostream>
#include <time.h>
#include "Wall.h"
#include "Coordinate.h"
#include "MazeChunkGeneration.h"

namespace console_maze { namespace maze {
	// The grid is represented by a 1D array where the rows are stored in sequential order of one another

	// Links are essentially walls
	// They represent the connections between the corners of each square
	// The coordinates represent the position of the top-left corner of a square where (0, 0) is the very top-left square's top-left corner
	// This does not keep track of top-right, bottom-left, bottom right corners (i.e. in a 1x1 grid there is only one coordinate (0, 0))
	// x increases the further right you go
	// y increases the further down you go

	enum Direction : uint8_t
	{
		RIGHT_DIRECTION,
		LEFT_DIRECTION,
		UP_DIRECTION,
		DOWN_DIRECTION,
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="coords"></param>
	/// <param name="bounds"></param>
	/// <returns></returns>
	int coordinateToIndex(common::Coordinate coords, common::Coordinate bounds)
	{
		return coords.y * bounds.x + coords.x;
	}

	void branch(uint8_t* wallSet, common::Coordinate coords, common::Coordinate bounds, bool* usedSquares, int linkIdentifier);
	bool inBounds(common::Coordinate coords, common::Coordinate bounds);
	void processLink(uint8_t* wallSet, int linkIdentifier, common::Coordinate bounds);
	void processVerticalLink(uint8_t* wallSet, int linkIdentifier, common::Coordinate bounds);
	void processHorizontalLink(uint8_t* wallSet, int linkIdentifier, common::Coordinate bounds);
	int countVerticalLinks(common::Coordinate bounds);
	int countHorizontalLinks(common::Coordinate bounds);
	int findBottomLink(common::Coordinate coords, common::Coordinate bounds);
	int findRightLink(common::Coordinate coords, common::Coordinate bounds);
	int findTopLink(common::Coordinate coords, common::Coordinate bounds);
	int findLeftLink(common::Coordinate coords, common::Coordinate bounds);

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

		common::Coordinate bounds = common::Coordinate{ width, height };
		// coordinate to begin maze generation from
		common::Coordinate startingCoord = common::Coordinate{ width / 2, height / 2 };

		for (int y = 0; y < bounds.y; y++)
		{
			for (int x = 0; x < bounds.x; x++)
			{
				common::Coordinate coords = common::Coordinate{ x, y };
				int location = coordinateToIndex(coords, bounds);
				// each unit in maze starts out as completely walled
				wallSet[location] = common::wall::EVERY_WALL;
				usedSquares[location] = false;
				//std::cout << (char)('A' + wallSet[location]) << std::endl;

			}
		}

		branch(wallSet, startingCoord, bounds, usedSquares, -1);

		return wallSet;
	}

	/// <summary>
	/// A recursive depth-first search algorithm
	/// Marks visited coordinates in the usedSquares array if visited already, when visited again it exits before branching
	/// Otherwise branches in all directions by calling itself on each adjacent coordinate
	/// </summary>
	/// <param name="wallSet">An array of integers each representing a square and the walls adjacent to it as defined in Wall.h</param>
	/// <param name="coords">A pair of integers representing location in the maze</param>
	/// <param name="bounds">A pair of integers representing the size of the maze</param>
	/// <param name="usedSquares">An array of booleans with each corresponding to a square in the maze, true is visited, false if not</param>
	/// <param name="linkIdentifier">An integer that represents the location of a wall</param>
	void branch(uint8_t* wallSet, common::Coordinate coords, common::Coordinate bounds, bool* usedSquares, int linkIdentifier)
	{
		int location = coordinateToIndex(coords, bounds);
		if (!inBounds(coords, bounds) || usedSquares[location]) {
			return;
		}

		usedSquares[location] = true;
		processLink(wallSet, linkIdentifier, bounds);

		Direction branchOrder[] = {
			UP_DIRECTION,
			DOWN_DIRECTION,
			RIGHT_DIRECTION,
			LEFT_DIRECTION,
		};
		int numPaths = 4;

		// generating random order of directions to go
		srand(time(NULL) * ((coords.x + 11) * (coords.y + 71) * 89) % 101); // seeding
		for (int toSwap = 0; toSwap < numPaths - 1; toSwap++)
		{
			int range = numPaths - toSwap; // amount that toSwap can be increased by
			int swapWith = rand() % range;

			Direction temp = branchOrder[toSwap];
			branchOrder[toSwap] = branchOrder[swapWith];
			branchOrder[swapWith] = temp;
		}

		// branching each direction once in random order
		for (int i = 0; i < numPaths; i++)
		{
			switch (branchOrder[i])
			{
			case RIGHT_DIRECTION:
				branch(wallSet, common::Coordinate{ coords.x + 1 , coords.y }, bounds, usedSquares, findRightLink(coords, bounds));
				break;
			case LEFT_DIRECTION:
				branch(wallSet, common::Coordinate{ coords.x - 1 , coords.y }, bounds, usedSquares, findLeftLink(coords, bounds));
				break;
			case DOWN_DIRECTION:
				branch(wallSet, common::Coordinate{ coords.x , coords.y + 1 }, bounds, usedSquares, findBottomLink(coords, bounds));
				break;
			case UP_DIRECTION:
				branch(wallSet, common::Coordinate{ coords.x , coords.y - 1 }, bounds, usedSquares, findTopLink(coords, bounds));
				break;
			}
		}

		return;
	}

	bool inBounds(common::Coordinate coords, common::Coordinate bounds)
	{
		return
			(coords.x < bounds.x&& coords.x >= 0) &&
			(coords.y < bounds.y&& coords.y >= 0);
	}

	int countVerticalLinks(common::Coordinate bounds)
	{
		return (bounds.y - 1) * bounds.x;
	}

	int countHorizontalLinks(common::Coordinate bounds)
	{
		return (bounds.x - 1) * bounds.y;
	}

	void processLink(uint8_t* wallSet, int linkIdentifier, common::Coordinate bounds)
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

	void processVerticalLink(uint8_t* wallSet, int linkIdentifier, common::Coordinate bounds)
	{
		int verticalLinkInd = linkIdentifier - countHorizontalLinks(bounds);

		int x = verticalLinkInd % bounds.x; // finding floored quotient of id and the number of columns in the grid
		int y = verticalLinkInd / bounds.x; // finding remainder of id and number of columns in the grid

		// find coordinate of square on top
		auto top = common::Coordinate{ x, y };
		// find coordinate of square on bottom
		auto btm = common::Coordinate{ x, y + 1 };

		int topLoc = coordinateToIndex(top, bounds);
		int btmLoc = coordinateToIndex(btm, bounds);

		// open top wall on wall to bottom of link
		wallSet[btmLoc] = wallSet[btmLoc] & compl common::wall::TOP_WALL;
	}

	void processHorizontalLink(uint8_t* wallSet, int linkIdentifier, common::Coordinate bounds)
	{
		int horizontalLinkInd = linkIdentifier;

		int x = horizontalLinkInd / bounds.y; // finding floored quotient of id and the number of rows in the grid
		int y = horizontalLinkInd % bounds.y; // finding remainder of id and number of rows in the grid

		// find coordinate of square to left
		auto left = common::Coordinate{ x, y };
		// find coordinate of square to right
		auto right = common::Coordinate{ x + 1, y };

		int leftLoc = coordinateToIndex(left, bounds);
		int rightLoc = coordinateToIndex(right, bounds);

		// open left wall on wall to right of link
		wallSet[rightLoc] = wallSet[rightLoc] & compl common::wall::LEFT_WALL;
	}

	/// <summary>
	/// Finds link to the bottom of a given coord
	/// </summary>
	/// <param name="coords"></param>
	/// <param name="bounds"></param>
	/// <returns></returns>
	int findBottomLink(common::Coordinate coords, common::Coordinate bounds)
	{
		return coords.y * bounds.x + coords.x + countHorizontalLinks(bounds);
	}

	/// <summary>
	/// Finds link to the right of a given coord
	/// </summary>
	/// <param name="coords"></param>
	/// <param name="bounds"></param>
	/// <returns></returns>
	int findRightLink(common::Coordinate coords, common::Coordinate bounds)
	{
		return coords.x * bounds.y + coords.y;
	}

	int findTopLink(common::Coordinate coords, common::Coordinate bounds)
	{
		return (coords.y - 1) * bounds.x + coords.x + countHorizontalLinks(bounds);
	}

	int findLeftLink(common::Coordinate coords, common::Coordinate bounds)
	{
		return (coords.x - 1) * bounds.y + coords.y;
	}

} }