#pragma once

class Ball
{
public:
	float x, y, dx, dy,r; //the position and velocity of a ball
	bool active;
	Ball(float r_): x(), y(),r(r_), dx(),
		dy(), active(false) {}
	void move();
};