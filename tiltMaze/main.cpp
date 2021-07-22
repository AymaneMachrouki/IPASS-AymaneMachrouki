#include <array>
#include "hwlib.hpp"
#include "MPU6050.hpp"
#include "gameObjects.hpp"

int main(){
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);

    auto calibrationButton = hwlib::target::pin_in(hwlib::target::pins::d53);
    auto resetButton = hwlib::target::pin_in(hwlib::target::pins::d52);

    hwlib::glcd_oled display = hwlib::glcd_oled( bus, 0x3c );
    
    auto font    = hwlib::font_default_8x8();
    auto winScreen = hwlib::terminal_from( display, font );

    MPU6050 sensor(0x68, bus);
    sensor.resetChip();
    sensor.wakeUp();
    sensor.setAccelerometerSensitivity(3);

    std::array<gameObjects, 19> gameMap = {
        gameObjects(127, 0, 127, 63),
        gameObjects(0, 0, 0, 63),
        gameObjects(0, 0, 127, 0),
        gameObjects(0, 63, 127, 63),

        gameObjects(15, 0, 15, 25),
        gameObjects(30, 0, 30, 25),
        gameObjects(30, 40, 30, 63),
        gameObjects(80, 40, 80, 63),
        gameObjects(100, 40, 100, 63),
        gameObjects(115, 0, 115, 20),
        gameObjects(70, 0, 70, 52),
        gameObjects(53, 20, 53, 40),
        gameObjects(90, 10, 90, 40),

        gameObjects(40, 52, 71, 52),
        gameObjects(10, 40, 54, 40),
        gameObjects(0, 52, 18, 52),
        gameObjects(30, 20, 40, 20),
        gameObjects(70, 30, 110, 30),
        gameObjects(100, 50, 115, 50)
    };

    int ballX = 5; 
    int ballY = 58;
    int calibrationX = 0;
    int calibrationY = 0;
    bool win = false;

    while(true){
        while(!win){ 
            display.clear();

            if(sensor.getAccellerationX() - calibrationX > 200) ballY--;
            else if(sensor.getAccellerationX() - calibrationX < -200) ballY++;
            if(sensor.getAccellerationY() - calibrationY > 200) ballX--;
            else if(sensor.getAccellerationY() - calibrationY < -200) ballX++;

            if(!calibrationButton.read()){
                calibrationX = sensor.getAccellerationX();
                calibrationY = sensor.getAccellerationY();
            }

            if(!resetButton.read()){
                ballX = 5; 
                ballY = 58;
            }

            hwlib::circle ball(hwlib::xy(ballX, ballY), 3);
            ball.draw(display);

            gameObjects finish(77, 19, 82, 24);
            finish.drawFinish(display);

            for(gameObjects& walls : gameMap){
                walls.drawWall(display);
                if(walls.checkCollision(ballX, ballY)){
                    if(ballX+4 <= walls.startX) ballX -=1;
                    else if(ballX-4 >= walls.endX) ballX +=1;
                    else if(ballY+4 <= walls.startY) ballY -=1;
                    else if(ballY-4 >= walls.endY) ballY +=1;
                }
            }

            if(finish.checkCollision(ballX, ballY)) win = true;    

            display.flush();
        }
        winScreen << "\f\n\n     YOU WIN\n\n    PRESS THE\n WHITE BUTTON TO\n   PLAY AGAIN!"; 

        if(!resetButton.read()){
            ballX = 5; 
            ballY = 58;
            win = false;
        }

        display.flush();
    }

    sensor.resetChip();
}