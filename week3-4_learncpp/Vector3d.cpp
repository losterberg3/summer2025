#include <iostream>
#include "headers/Vector3d.h"

void Vector3d::print() const
{
	std::cout << "Vector(" << m_x << ", " << m_y << ", " << m_z << ")\n";
}
