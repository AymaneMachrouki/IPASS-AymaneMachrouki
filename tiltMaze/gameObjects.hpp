#ifndef GAMEOBJECTS_HPP
#define GAMEOBJECTS_HPP
#include "hwlib.hpp"

/// @file

/// \brief
/// Class for the game objects.
/// \details
/// This class creates game objects and provides functions for them.
/// It only accepts hwlib lines and rectangles.

class gameObjects{
public:
   int startX;
   int startY;
   int endX;
   int endY;

   /// \brief
   /// Initilizes values.
   /// \details
   /// This is the class's constructor which initilizes the startX, startY, endX and endY of an game object.
	gameObjects(int startX, int startY, int endX, int endY);

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
   /// This function checks if two objects are colliding with each other.
	bool checkCollision(int ballX, int ballY);
};

#endif
