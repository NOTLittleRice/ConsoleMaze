#include <iostream>
#include "mazeChunkGeneration.h"
#include "Wall.h"

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

// Do not stage: only a basic idea
class MazeChunk
{
private:
	MazeUnit* m_units;
	int m_width, m_height;

public:
	MazeChunk(MazeUnit* units, int width, int height)
	{
		this->m_units = units;
		this->m_width = width;
		this->m_height = height;
	}
};

enum MAZE_UNIT_SIZE_IN_BUFFER
{
	//UNIT_WIDTH_IN_BUFFER = 4,
	//UNIT_HEIGHT_IN_BUFFER = 2
	UNIT_WIDTH_IN_BUFFER = 6,
	UNIT_HEIGHT_IN_BUFFER = 4
};

int calcBufferForWidth(int width);
int calcBufferForHeight(int height);

// width and height describe dimensions of the maze
// assumes the buffer correlates to the maze's dimensions where
// maze_width * 2 + 1 matches width
// maze_height * 2 + 1 matches height
void populateBuffer(MazeUnit* maze, char* buffer, int width, int height)
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
			auto walls = (maze + i*width + j)->GetWalls();
			char charUsed = ' ';
			int topLeftCorner =
				UNIT_WIDTH_IN_BUFFER * j + // shift based on x dimension within maze
				UNIT_HEIGHT_IN_BUFFER * i * rowPixelWidth;// shift based on y dimension within maze
				
			buffer[topLeftCorner] = cornerChar; // top left corner of square
			buffer[topLeftCorner + UNIT_WIDTH_IN_BUFFER] = cornerChar; // top right corner of square
			buffer[topLeftCorner + UNIT_HEIGHT_IN_BUFFER * rowPixelWidth] = cornerChar; // bottom left corner of square
			buffer[topLeftCorner + UNIT_HEIGHT_IN_BUFFER * rowPixelWidth + UNIT_WIDTH_IN_BUFFER] = cornerChar; // bottom right corner of square

			if (((walls & RIGHT_WALL) >> RIGHT_WALL_BIT) % 2)
			{
				charUsed = wallChar;
			}
			else
			{
				charUsed = unoccupiedChar;
			}
			for (int i = 1; i < UNIT_HEIGHT_IN_BUFFER; i++)
			{
				buffer[topLeftCorner + (rowPixelWidth * i) + UNIT_WIDTH_IN_BUFFER] = charUsed;
			}

			if (((walls & LEFT_WALL) >> LEFT_WALL_BIT) % 2)
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

			if (((walls & BOTTOM_WALL) >> BOTTOM_WALL_BIT) % 2)
			{
				charUsed = floorChar;
			}
			else
			{
				charUsed = unoccupiedChar;
			}
			for (int i = 1; i < UNIT_WIDTH_IN_BUFFER; i++)
			{
				buffer[topLeftCorner + UNIT_HEIGHT_IN_BUFFER * rowPixelWidth + i] = charUsed;
			}

			if (((walls & TOP_WALL) >> TOP_WALL_BIT) % 2)
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

void LoadConfiguration(int width, int height, uint8_t* wallConfiguration)
{
	//int width = 2, height = 5; // represent dimensions of maze
	char* mazeBuffer = (char*)malloc(calcBufferGridSize(width, height));

	MazeUnit* h = (MazeUnit*)malloc(sizeof(MazeUnit) * width * height);

	if (h == nullptr)
	{
		throw;
	}

	auto bounds = Coordinate{ width, height };
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			auto coords = Coordinate{ x, y };
			int location = coordinateToIndex(coords, bounds);
			h[location] = MazeUnit(wallConfiguration[location]);
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

int main()
{
	//emptyCenter();
	//std::cout << std::endl;
	//S();

	int width = 30;
	int height = 10;
	uint8_t* wallConfiguration = generateWallConfigurations(width, height);
	LoadConfiguration(width, height, wallConfiguration);
}
