#include <array>
#include "hwlib.hpp"
#include "MPU6050.hpp"
#include "walls.hpp"

int main(){
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);

    auto button = hwlib::target::pin_in(hwlib::target::pins::d53);

    hwlib::glcd_oled display = hwlib::glcd_oled( bus, 0x3c ); 

    MPU6050 sensor(0x68, bus);
    sensor.wakeUp();
    sensor.setAccelerometerSensitivity(3);

    std::array<walls, 20> gameMap = {
        walls(127, 0, 127, 63),
        walls(0, 0, 0, 63),
        walls(0, 0, 127, 0),
        walls(0, 63, 127, 63),

        walls(15, 0, 15, 25),
        walls(30, 0, 30, 25),
        walls(30, 40, 30, 63),
        walls(80, 40, 80, 63),
        walls(100, 40, 100, 63),
        walls(115, 0, 115, 20),
        walls(70, 0, 70, 53),
        walls(53, 20, 53, 40),
        walls(90, 10, 90, 40),

        walls(40, 52, 70, 52),
        walls(10, 40, 30, 40),
        walls(0, 50, 20, 50),
        walls(30, 20, 40, 20),
        walls(20, 40, 60, 40),
        walls(70, 30, 110, 30),
        walls(100, 50, 115, 50)
    };

    int ballX = 5; 
    int ballY = 58;
    int calibrationX = 0;
    int calibrationY = 0;

    while(true){ 
        display.clear();

        if(sensor.getAccellerationX() - calibrationX > 200){
            ballY--;
        }
        else if(sensor.getAccellerationX() - calibrationX < -200){
            ballY++;
        }
        if(sensor.getAccellerationY() - calibrationY > 200){
            ballX--;
        }
        else if(sensor.getAccellerationY() - calibrationY < -200){
            ballX++;
        }

        if(!button.read()){
            calibrationX = sensor.getAccellerationX();
            calibrationY = sensor.getAccellerationY();
        }

        hwlib::cout << sensor.getGyroX() << hwlib::endl;

        hwlib::circle ball(hwlib::xy(ballX, ballY), 3);
        ball.draw(display);

        for(walls& walls : gameMap){
            walls.drawWall(display);
            if(walls.checkCollision(ballX, ballY)){
                if(ballX+4 <= walls.startX) ballX -=1;
                else if(ballX-4 >= walls.endX) ballX +=1;
                else if(ballY+4 <= walls.startY) ballY -=1;
                else if(ballY-4 >= walls.endY) ballY +=1;
            }
        }

        display.flush();
    }   
}