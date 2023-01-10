#include <iostream>

class MazeUnit
{
private:
	uint8_t m_walls;

public:
	MazeUnit(uint8_t walls)
	{
		this->m_walls = walls;
	}

	uint8_t GetWalls()
	{
		return this->m_walls;
	}

};

enum WallBit : uint8_t
{
	RIGHT_WALL_BIT = 0,
	BOTTOM_WALL_BIT,
	LEFT_WALL_BIT,
	TOP_WALL_BIT
};

enum Wall : uint8_t
{
	RIGHT_WALL	= 1 << RIGHT_WALL_BIT,	// 0001
	BOTTOM_WALL = 1 << BOTTOM_WALL_BIT, // 0010
	LEFT_WALL	= 1 << LEFT_WALL_BIT,	// 0100
	TOP_WALL	= 1 << TOP_WALL_BIT		// 1000
};

int calcBufferForDimension(int dimension);

// width and height describe dimensions of the maze
// assumes the buffer correlates to the maze's dimensions where
// maze_width * 2 + 1 matches width
// maze_height * 2 + 1 matches height
void populateBuffer(MazeUnit* maze, char* buffer, int width, int height)
{
	int rowPixelWidth = calcBufferForDimension(width);
	char cornerChar = '*';
	char wallChar = '|';
	char floorChar = '-';
	char unoccupiedChar = ' ';
	
	for (int i = 0; i < height; i++) // y dimension within maze
	{
		for (int j = 0; j < width; j++) // x dimension within maze
		{
			auto walls = (maze + i*width + j)->GetWalls();

			char charUsed = ' ';
			//if (!(i % 2) && !(j % 2)) // if in a corner
			int topLeftCorner =
				2 * j + // shift based on x dimension within maze
				2 * i * rowPixelWidth;// shift based on y dimension within maze
				
			buffer[topLeftCorner] = cornerChar; // top left corner of square
			buffer[topLeftCorner + 2] = cornerChar; // top right corner of square
			buffer[topLeftCorner + 2 * rowPixelWidth] = cornerChar; // bottom left corner of square
			buffer[topLeftCorner + 2 * rowPixelWidth + 2] = cornerChar; // bottom right corner of square

			if (((walls & RIGHT_WALL) >> RIGHT_WALL_BIT) % 2)
			{
				charUsed = wallChar;
			}
			else
			{
				charUsed = unoccupiedChar;
			}
			buffer[topLeftCorner + rowPixelWidth + 2] = charUsed;

			if (((walls & LEFT_WALL) >> LEFT_WALL_BIT) % 2)
			{
				charUsed = wallChar;
			}
			else
			{
				charUsed = unoccupiedChar;
			}
			buffer[topLeftCorner + rowPixelWidth] = charUsed;

			if (((walls & BOTTOM_WALL) >> BOTTOM_WALL_BIT) % 2)
			{
				charUsed = floorChar;
			}
			else
			{
				charUsed = unoccupiedChar;
			}
			buffer[topLeftCorner + 2 * rowPixelWidth + 1] = charUsed;

			if (((walls & TOP_WALL) >> TOP_WALL_BIT) % 2)
			{
				charUsed = floorChar;
			}
			else {
				charUsed = unoccupiedChar;
			}
			buffer[topLeftCorner + 1] = charUsed;

			//fill in center
			buffer[topLeftCorner + rowPixelWidth + 1] = 'o';
		}
	}
}

int calcBufferForDimension(int dimension)
{
	return dimension * 2 + 1;
}

int calcBufferGridSize(int width, int height)
{
	return calcBufferForDimension(width) * calcBufferForDimension(height);
}

void emptyCenter()
{
	int width = 3, height = 3; // represent dimensions of maze
	char* mazeBuffer = (char*)malloc(calcBufferGridSize(width, height));

	MazeUnit h[] = {
		MazeUnit(BOTTOM_WALL | RIGHT_WALL | LEFT_WALL | TOP_WALL),
		MazeUnit(RIGHT_WALL | LEFT_WALL | TOP_WALL),
		MazeUnit(BOTTOM_WALL | RIGHT_WALL | LEFT_WALL | TOP_WALL),

		MazeUnit(BOTTOM_WALL | LEFT_WALL | TOP_WALL),
		MazeUnit(0),
		MazeUnit(BOTTOM_WALL | RIGHT_WALL | TOP_WALL),

		MazeUnit(BOTTOM_WALL | RIGHT_WALL | LEFT_WALL | TOP_WALL),
		MazeUnit(BOTTOM_WALL | RIGHT_WALL | LEFT_WALL),
		MazeUnit(BOTTOM_WALL | RIGHT_WALL | LEFT_WALL | TOP_WALL),
	};
	//std::cout << (int)h.GetWalls();
	populateBuffer(h, mazeBuffer, width, height);

	int bufferWidth = calcBufferForDimension(width);
	char* rowBuffer = (char*)malloc(bufferWidth + 1);
	rowBuffer[bufferWidth] = '\0';
	std::cout << std::endl;

	int bufferHeight = calcBufferForDimension(height);
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
	char* mazeBuffer = (char*)malloc(calcBufferGridSize(width, height));

	MazeUnit h[] = {
		MazeUnit(TOP_WALL | LEFT_WALL),
		MazeUnit(TOP_WALL | RIGHT_WALL),

		MazeUnit(LEFT_WALL | RIGHT_WALL),
		MazeUnit(LEFT_WALL | RIGHT_WALL | BOTTOM_WALL),

		MazeUnit(LEFT_WALL | BOTTOM_WALL),
		MazeUnit(TOP_WALL | RIGHT_WALL),

		MazeUnit(TOP_WALL | LEFT_WALL | RIGHT_WALL),
		MazeUnit(LEFT_WALL | RIGHT_WALL),

		MazeUnit(LEFT_WALL | BOTTOM_WALL),
		MazeUnit(RIGHT_WALL | BOTTOM_WALL),

	};
	//std::cout << (int)h.GetWalls();
	populateBuffer(h, mazeBuffer, width, height);

	int bufferWidth = calcBufferForDimension(width);
	char* rowBuffer = (char*)malloc(bufferWidth + 1);
	rowBuffer[bufferWidth] = '\0';
	std::cout << std::endl;

	int bufferHeight = calcBufferForDimension(height);
	for (int row = 0; row < bufferHeight; row++)
	{
		strncpy_s(rowBuffer, bufferWidth + 1, mazeBuffer + (bufferWidth * row), bufferWidth);
		std::cout << rowBuffer << std::endl;
	}

	free(mazeBuffer);
	free(rowBuffer);
}

int main()
{
	emptyCenter();
	std::cout << std::endl;
	S();
}
