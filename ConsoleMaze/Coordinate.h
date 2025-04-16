#pragma once

namespace console_maze {
namespace common {

struct Coordinate
{
	int x, y;
};

static Coordinate ORIGIN = Coordinate{0, 0};

int product(Coordinate c);
bool boundBy(Coordinate current, Coordinate topLeft, Coordinate bottomRight);

} }