#pragma once
#include "Coordinate.h"
#include <corecrt_malloc.h>

namespace console_maze {
namespace maze {
namespace display {

class CharBuffer
{
private:
	char* m_buffer;
	common::Coordinate m_dimensions;

public:
	CharBuffer(common::Coordinate dimensions)
	{
		m_dimensions = dimensions;
		m_buffer = (char*)malloc(sizeof(char) * m_dimensions.x * m_dimensions.y);
	}

	~CharBuffer()
	{
		if (m_buffer)
		{
			free(m_buffer);
		}
	}

	bool bufferExists()
	{
		return m_buffer != nullptr;
	}

	void clear()
	{
		if (bufferExists())
		{
			for (int i = 0; i < common::product(m_dimensions); i++)
			{
				m_buffer[i] = ' ';
			}
		}
	}

	bool setChar(common::Coordinate coord, char c)
	{
		if (bufferExists())
		{
			if (common::boundBy(
				coord,
				common::ORIGIN, 
				m_dimensions)
			)
			{
				m_buffer[coord.y * m_dimensions.x + coord.x] = c;
			}
		}
	}
// note to self do not interface abstract ideas of offsetting by a passed amount into here, should be defined in camera
};

}
}
}