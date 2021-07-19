#include "hwlib.hpp"
#include "MPU6050.hpp"
#include <array>

int main (){
    auto scl1 = hwlib::target::pin_oc(hwlib::target::pins::scl1);
    auto sda1 = hwlib::target::pin_oc(hwlib::target::pins::sda1);
    auto bus = hwlib::i2c_bus_bit_banged_scl_sda(scl1, sda1);

    MPU6050 sensor(0x68, bus);
    sensor.wakeUp();
    hwlib::cout << sensor.whoAmI() << hwlib::endl; //returns 114?????
    sensor.resetGyroscope();
    hwlib::wait_ms(20);
    hwlib::cout << sensor.getTemperature() << hwlib::endl;
    hwlib::cout << sensor.getTemperature() << hwlib::endl;
    hwlib::cout << sensor.getTemperature() << hwlib::endl;
    hwlib::cout << sensor.getTemperature() << hwlib::endl;
    sensor.resetChip();

	auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
	auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
   
	auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    hwlib::glcd_oled display = hwlib::glcd_oled( i2c_bus, 0x3c ); 
    int i = 0;
    while(true){ 
     
        display.clear();
        
        hwlib::line ground(hwlib::xy(0, 10), hwlib::xy(128, 10));
        ground.draw(display);

        hwlib::circle sun(hwlib::xy(10, 55), (8+i));
        sun.draw(display);
        hwlib::cout << i << hwlib::endl;
        
        i = i +10;
        display.flush();
    }   
}