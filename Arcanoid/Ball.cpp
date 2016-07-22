#include"Ball.h"
#include "vars.h"

void Ball::move()
{
	x += dx;
	y += dy;
	if (x - r <= 0)
	{
		x = r;
		dx *= -1;
	}
	else if (y - r <= 0)
	{
		y = r;
		dy *= -1;
	}
	else if (x + r >= 300)
	{
		x = 300 - r;
		dx *= -1;
	}
	else if (y + r >= r_y && y + r <= r_y + r_h &&x > r_x && x < r_x + r_w)
	{
		y = r_y - r;
		dy *= -1;

	}
	//a ball went out for the bottom border
	else if (y > 300)
		active = false; //a ball returns to the racket
}