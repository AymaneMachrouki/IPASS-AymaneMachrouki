#include "hwlib.hpp"
#include "MPU6050.hpp"

//These tests are designed to check if all library functions are working. 
//However it is advised to test functions like the getGyro and get Acceleration functions yourself by moving the chip around and checking the values.

//For this test the whoAmI needs to return either 0x68 or 0x69. 
//Those are it's only possible adresses.
void testWhoAmI(MPU6050 sensor){
    if(sensor.whoAmI() == 0x68 || sensor.whoAmI() == 0x69) hwlib::cout << "whoAmI works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "whoAmI isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test the readRegister will read the whoAmI register. 
//It should return either 0x68 or 0x69.
void testReadRegister(MPU6050 sensor, int registerAdress){
    if(sensor.readRegister(registerAdress) == sensor.whoAmI()) hwlib::cout << "readRegister works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "readRegister isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test the readRegister will read the setAccelerometerSensitivity register. 
//If the sensitivty is correctly set to 3, it should return 24.
void testSetAccelerometerSensitivity(MPU6050 sensor){
    sensor.setAccelerometerSensitivity(3);
    if(sensor.readRegister(0x1C) == 24) hwlib::cout << "setAccelerometerSensitivity works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "setAccelerometerSensitivity isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test the readRegister will read the setGyroscopeSensitivity register. 
//If the sensitivty is correctly set to 3, it should return 24.
void testSetGyroscopeSensitivity(MPU6050 sensor){
    sensor.setGyroscopeSensitivity(3);
    if(sensor.readRegister(0x1B) == 24) hwlib::cout << "setGyroscopeSensitivity works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "setGyroscopeSensitivity isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test it is required that the area you are in has a room temperature.
//This test will check if the getTemperature returns a realistic temperature.
void testGetTemperature(MPU6050 sensor){
    sensor.resetTemperature();
    if(sensor.getTemperature() > 10 && sensor.getTemperature() < 40) hwlib::cout << "getTemperature works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "getTemperature isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test it is required that the sensor is put on a flat surface and that it isn't moving.
//This will check if the getAccellerationX returns a realistic value.
//There is a chance that this won't work because of your location. 
//If that happens use the while loop in the main to check the values yourself.
void testGetAccellerationX(MPU6050 sensor){
    sensor.resetAccelerometer();
    sensor.setAccelerometerSensitivity(0);
    if(sensor.getAccellerationX() < 120 && sensor.getAccellerationX() > -30) hwlib::cout << "getAccellerationX works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "getAccellerationX isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test it is required that the sensor is put on a flat surface and that it isn't moving.
//This will check if the getAccellerationY returns a realistic value.
//There is a chance that this won't work because of your location. 
//If that happens use the while loop in the main to check the values yourself.
void testGetAccellerationY(MPU6050 sensor){
    sensor.resetAccelerometer();
    sensor.setAccelerometerSensitivity(0);
    if(sensor.getAccellerationY() < 120 && sensor.getAccellerationY() > -30) hwlib::cout << "getAccellerationY works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "getAccellerationY isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test it is required that the sensor is put on a flat surface that it isn't moving.
//This will check if the getAccellerationZ returns a realistic value.
//There is a chance that this won't work because of your location. 
//If that happens use the while loop in the main to check the values yourself.
void testGetAccellerationZ(MPU6050 sensor){
    sensor.resetAccelerometer();
    sensor.setAccelerometerSensitivity(0);
    if(sensor.getAccellerationZ() < 6000 && sensor.getAccellerationZ() > -30) hwlib::cout << "getAccellerationZ works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "getAccellerationZ isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test it is required that the sensor is put on a flat surface and that it isn't moving.
//This will check if the getGyroX returns a realistic value.
void testGetGyroX(MPU6050 sensor){
    sensor.resetGyroscope();
    sensor.setGyroscopeSensitivity(0);
    if(sensor.getGyroX() < 30 && sensor.getGyroX() > -30) hwlib::cout << "getGyroX works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "getGyroX isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test it is required that the sensor is put on a flat surface and that it isn't moving.
//This will check if the getGyroY returns a realistic value.
void testGetGyroY(MPU6050 sensor){
    sensor.resetGyroscope();
    sensor.setGyroscopeSensitivity(0);
    if(sensor.getGyroY() < 100 && sensor.getGyroY() > -30) hwlib::cout << "getGyroY works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "getGyroY isn't working correctly!" << hwlib::endl << hwlib::endl;
}

//For this test it is required that the sensor is put on a flat surface and that it isn't moving.
//This will check if the getGyroZ returns a realistic value.
void testGetGyroZ(MPU6050 sensor){
    sensor.resetGyroscope();
    sensor.setGyroscopeSensitivity(0);
    if(sensor.getGyroZ() < 30 && sensor.getGyroZ() > -30) hwlib::cout << "getGyroZ works!" << hwlib::endl << hwlib::endl;
    else hwlib::cout << "getGyroZ isn't working correctly!" << hwlib::endl << hwlib::endl;
}

int main(){
    auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto bus = hwlib::i2c_bus_bit_banged_scl_sda(scl,sda);

    MPU6050 sensor(0x68, bus);
    sensor.resetChip();
    sensor.wakeUp();
    
    testWhoAmI(sensor); 
    testReadRegister(sensor, 0x75); 
    testSetAccelerometerSensitivity(sensor);
    testSetGyroscopeSensitivity(sensor);
    testGetTemperature(sensor);
    testGetAccellerationX(sensor); 
    testGetAccellerationY(sensor);
    testGetAccellerationZ(sensor);
    testGetGyroX(sensor);
    testGetGyroY(sensor);
    testGetGyroZ(sensor);

//This while loop is used to check if the values are still realistic when moving around.
//Uncomment the while loop and function that you want to test.

    // while(true){
    //     //hwlib::cout << "AccelerationX = " << sensor.getAccellerationX() << hwlib::endl;
    //     //hwlib::cout << "AccelerationY = " << sensor.getAccellerationX() << hwlib::endl;
    //     //hwlib::cout << "AccelerationZ = " << sensor.getAccellerationX() << hwlib::endl;
    //     //hwlib::cout << "GyroX = " << sensor.getGyroX() << hwlib::endl;
    //     //hwlib::cout << "GyroY = " << sensor.getGyroY() << hwlib::endl;
    //     //hwlib::cout << "GyroZ = " << sensor.getGyroZ() << hwlib::endl;
    //     //hwlib::cout << "Temperature = " << sensor.getTemperature() << hwlib::endl;
    // }
}