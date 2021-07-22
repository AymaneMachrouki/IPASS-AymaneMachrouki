#include "gameObjects.hpp"

gameObjects::gameObjects(int startX, int startY, int endX, int endY):
    startX(startX),
    startY(startY),
    endX(endX),
    endY(endY)
{}

void gameObjects::drawFinish(hwlib::glcd_oled & display){
    hwlib::rectangle finish(hwlib::xy(startX, startY), hwlib::xy(endX, endY));
    finish.draw(display);
}

void gameObjects::drawWall(hwlib::glcd_oled & display){
    hwlib::line wall(hwlib::xy(startX, startY), hwlib::xy(endX, endY));
    wall.draw(display);
}

bool gameObjects::checkCollision(int ballX, int ballY){
    if(ballY+5 > startY && ballY-5 < endY && ballX+5 > startX && ballX-5 < endX) return true;
    return false;
}
