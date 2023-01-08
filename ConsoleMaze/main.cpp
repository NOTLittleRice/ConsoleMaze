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

	__int8 GetWalls()
	{
		return this->m_walls;
	}

};

enum Wall : uint8_t
{
	RIGHT_WALL	= 1 << 0, // 0001
	BOTTOM_WALL = 1 << 1, // 0010
	LEFT_WALL	= 1 << 2, // 0100
	TOP_WALL	= 1 << 3  // 1000
};

// width and height describe dimensions of the buffer
// assumes the buffer correlates to the maze's dimensions where
// maze_width * 2 + 1 matches width
// maze_height * 2 + 1 matches height
void populateBuffer(MazeUnit* maze, char* buffer, int width, int height)
{
	// only works for a 1 x 1 maze with a 3 x 3 buffer
	for (int i = 0; i < (height-1) / 2; i++) // y dimension within maze
	{
		for (int j = 0; j < (width-1) / 2; j++) // x dimension within maze
		{
			auto walls = (maze + i*(width-2) + j)->GetWalls();

			char charUsed = ' ';
			//if (!(i % 2) && !(j % 2)) // if in a corner
			int topLeftCorner =
				2 * j + // shift based on x dimension within maze
				2 * i * // shift based on y dimension within maze
				((width * 2) + 1);
			buffer[topLeftCorner] = '*'; // top left corner of square
			buffer[topLeftCorner + 2] = '*'; // top right corner of square
			buffer[topLeftCorner + 2 * (((width-2) * 2) + 1)] = '*'; // bottom left corner of square
			buffer[topLeftCorner + 2 * (((width-2) * 2) + 1) + 2] = '*'; // bottom right corner of square

			auto rowPixelWidth = (width - 2) * 2 + 1;
			
			if (((walls & RIGHT_WALL) >> 0) % 2)
			{
				charUsed = '|';
			}
			else
			{
				charUsed = ' ';
			}
			buffer[topLeftCorner + rowPixelWidth + 2] = charUsed;

			if (((walls & LEFT_WALL) >> 2) % 2)
			{
				charUsed = '|';
			}
			else
			{
				charUsed = ' ';
			}
			buffer[topLeftCorner + rowPixelWidth] = charUsed;

			if (((walls & BOTTOM_WALL) >> 1) % 2)
			{
				charUsed = '-';
			}
			else
			{
				charUsed = ' ';
			}
			buffer[topLeftCorner + 2 * rowPixelWidth + 1] = charUsed;

			if (((walls & TOP_WALL) >> 3) % 2)
			{
				charUsed = '-';
			}
			else {
				charUsed = ' ';
			}
			buffer[topLeftCorner + 1] = charUsed;


			//fill in center
			buffer[topLeftCorner + rowPixelWidth + 1] = 'O';
		}
	}
}

int main()
{
	int width = 3, height = 3;
	char* mazeBuffer = (char*)malloc(width * height);
	
	auto h = MazeUnit(BOTTOM_WALL | RIGHT_WALL | LEFT_WALL);
	std::cout << (int)h.GetWalls();
	populateBuffer(&h, mazeBuffer, width, height);

	char* rowBuffer = (char*)malloc(width + 1);
	rowBuffer[width] = '\0';
	std::cout << std::endl;
	for (int row = 0; row < height; row++)
	{
		strncpy_s(rowBuffer, width+1, mazeBuffer + (width * row), width);
		std::cout << rowBuffer << std::endl;
	}
	
	free(mazeBuffer);
	free(rowBuffer);
}
