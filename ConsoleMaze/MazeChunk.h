#pragma once
#include "MazeUnit.h"

namespace console_maze {
namespace maze {

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

} }