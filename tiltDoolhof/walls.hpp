#ifndef WALLS_HPP
#define WALLS_HPP
#include "hwlib.hpp"

class walls{
public:
   int startX;
   int startY;
   int endX;
   int endY;
	walls(int startX, int startY, int endX, int endY);
	void drawWall(hwlib::glcd_oled & display);
	bool checkCollision(int ballX, int ballY);
};

#endif
