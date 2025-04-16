#pragma once
#include <iostream>

namespace console_maze {
namespace maze {

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

// maybe move coordsToIndex here

} }