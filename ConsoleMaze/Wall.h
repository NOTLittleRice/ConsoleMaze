#pragma once

namespace console_maze { namespace common { namespace wall {

enum WallBit : uint8_t
{
	LEFT_WALL_BIT = 0,
	TOP_WALL_BIT,
	NUM_BITS // can be used to make adjacent bits for determining whether or not wall is visible
};

enum Wall : uint8_t
{
	LEFT_WALL	= 1 << LEFT_WALL_BIT,	// 01
	TOP_WALL	= 1 << TOP_WALL_BIT,	// 10
	EVERY_WALL = LEFT_WALL | TOP_WALL
};

} } }