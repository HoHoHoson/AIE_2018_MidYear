#pragma once

#include "Matrix3.h"

struct Death
{

};

class Obstacle
{
public:
	Obstacle();
	~Obstacle();

private:

	float m_ProgressiveTimer = 0;
};
