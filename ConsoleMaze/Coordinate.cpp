#include "Coordinate.h"

namespace console_maze {
namespace common {

int product(Coordinate c)
{
	return c.x * c.y;
}

bool boundBy(Coordinate current, Coordinate topLeft, Coordinate bottomRight)
{
	return
		(current.x >= topLeft.x && current.x < bottomRight.x) &&
		(current.y >= topLeft.y && current.y < bottomRight.y);		
}

}}