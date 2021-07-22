#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP
#include "hwlib.hpp"

/// @file

/// \brief
/// Class for the game objects.
/// \details
/// This class creates game objects and provides functions for them.

class gameObjects{
public:
   int startX;
   int startY;
   int endX;
   int endY;
   int ballX;
   int ballY;
   int radius;

   /// \brief
   /// Initilizes values.
   /// \details
   /// This is the class's constructor which initilizes the startX, startY, endX and endY of a wall or finish game object.
	gameObjects(int startX, int startY, int endX, int endY);

   /// \brief
   /// Initilizes values.
   /// \details
   /// This is the class's constructor which initilizes the ballX, ballY and radius of a ball game object.
   gameObjects(int ballX, int ballY, int radius);

   /// \brief
   /// Draws ball.
   /// \details
   /// This function creates and draws a game object as a ball.
   void drawBall(hwlib::glcd_oled & display);

   /// \brief
   /// Draws wall.
   /// \details
   /// This function creates and draws a game object as a wall.
	void drawWall(hwlib::glcd_oled & display);

   /// \brief
   /// Draws finish.
   /// \details
   /// This function creates and draws a game object as a finsih.
   void drawFinish(hwlib::glcd_oled & display);

   /// \brief
   /// Checks collision.
   /// \details
   /// This function checks if the ball is colliding with a wall or finish.
	bool checkCollision(int ballX, int ballY);
};

#endif
