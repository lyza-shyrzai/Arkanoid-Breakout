#pragma once

class Brick
{
public:
	bool active;
	//grid
	short row, col, hit;
	float w, h;
	Brick(short r_, short c_, float w_, float h_, short hit_) :
		row(r_), col(c_), hit(h_), w(w_), h(h_), active(false) {};
	Brick(): row(), col(), w(20),h(20), hit(1), active(false) {};
};