#include "gameObjects.hpp"

gameObjects::gameObjects(int startX, int startY, int endX, int endY):
    startX(startX),
    startY(startY),
    endX(endX),
    endY(endY)
{}

gameObjects::gameObjects(int ballX, int ballY, int radius):
    ballX(ballX),
    ballY(ballY),
    radius(radius)
{}

void gameObjects::drawFinish(hwlib::glcd_oled & display){
    hwlib::rectangle finish(hwlib::xy(startX, startY), hwlib::xy(endX, endY));
    finish.draw(display);
}

void gameObjects::drawBall(hwlib::glcd_oled & display){
    hwlib::circle ball(hwlib::xy(ballX, ballY), radius);
    ball.draw(display);
}

void gameObjects::drawWall(hwlib::glcd_oled & display){
    hwlib::line wall(hwlib::xy(startX, startY), hwlib::xy(endX, endY));
    wall.draw(display);
}

bool gameObjects::checkCollision(int collisonBallX, int collisonBallY){
    if(collisonBallY+5 > startY && collisonBallY-5 < endY && collisonBallX+5 > startX && collisonBallX-5 < endX) return true;
    return false;
}