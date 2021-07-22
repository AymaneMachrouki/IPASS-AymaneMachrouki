#include "MPU6050.hpp"
#include "hwlib.hpp"
#include <array>

std::array<float, 4> gyroscopeSensitivities = {131, 65.5, 32.8, 16.4};
std::array<int, 4> accelerometerSensitivities = {16384, 8192, 4096, 2048};

void MPU6050::wakeUp(){
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x6B);
        writeTransaction.write(0x00);
    }
}

int MPU6050::whoAmI(){
    uint8_t data[1];
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x75);
    }
    {
        auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
        readTransaction.read(data, 1);
    }
    return data[0];
}

uint8_t MPU6050::readRegister(uint8_t registerAdress){
    uint8_t data[1];
    if(registerAdress < 0x0D || registerAdress > 0x76){
        hwlib::cout << "This register doesn't exist, now returning 0" << hwlib::endl;
        return 0;
    }
    else{
        {
            auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
            writeTransaction.write(registerAdress);
        }
        {
            auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
            readTransaction.read(data, 1);
        }
        return data[0];
    }
}

void MPU6050::setAccelerometerSensitivity(uint8_t fullScaleRange){
    if(fullScaleRange > 3) hwlib::cout << "This full scale range doesn't exist" << hwlib::endl;
    else{
        accelerometerSensitivity = accelerometerSensitivities[fullScaleRange];
        fullScaleRange = fullScaleRange << 3;
        {
            auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
            writeTransaction.write(0x1C);
            writeTransaction.write(fullScaleRange);
        }
    }
}

void MPU6050::setGyroscopeSensitivity(uint8_t fullScaleRange){
    if(fullScaleRange > 3) hwlib::cout << "This full scale range doesn't exist" << hwlib::endl;
    else{
        gyroscopeSensitivity = gyroscopeSensitivities[fullScaleRange];
        fullScaleRange = fullScaleRange << 3;
        {
            auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
            writeTransaction.write(0x1B);
            writeTransaction.write(fullScaleRange);
        }
    }
}

int16_t MPU6050::getTemperature(){
    int16_t temperature;
    uint8_t data[2];
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x41);
    }
    {
        auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
        readTransaction.read(data, 2);
    }
    temperature = (data[0] << 8) | data[1];
    temperature = temperature / 340 + 36.53;
    return temperature;
}

void MPU6050::resetTemperature(){
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x68);
        writeTransaction.write(0x01);
    }
}

int16_t MPU6050::getAccellerationX(){
    int16_t accellerationX;
    uint8_t data[2];
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x3B);
    }
    {
        auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
        readTransaction.read(data, 2);
    }
    accellerationX = (data[0] << 8) | data[1];
    accellerationX = accellerationX / (accelerometerSensitivity / 1000);
    return accellerationX;
}

int16_t MPU6050::getAccellerationY(){
    int16_t accellerationY;
    uint8_t data[2];
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x3D);
    }
    {
        auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
        readTransaction.read(data, 2);
    }
    accellerationY = (data[0] << 8) | data[1];
    accellerationY = accellerationY / (accelerometerSensitivity / 1000);
    return accellerationY;
}

int16_t MPU6050::getAccellerationZ(){
    int16_t accellerationZ;
    uint8_t data[2];
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x3F);
    }
    {
        auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
        readTransaction.read(data, 2);
    }
    accellerationZ = (data[0] << 8) | data[1];
    accellerationZ = accellerationZ / (accelerometerSensitivity / 1000);
    return accellerationZ;
}

void MPU6050::resetAccelerometer(){
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x68);
        writeTransaction.write(0x02);
    }
}

int16_t MPU6050::getGyroX(){
    int16_t gyroX;
    uint8_t data[2];
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x43);
    }
    {
        auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
        readTransaction.read(data, 2);
    }
    gyroX = (data[0] << 8) | data[1];
    gyroX = gyroX / gyroscopeSensitivity;
    return gyroX;
}

int16_t MPU6050::getGyroY(){
    int16_t gyroY;
    uint8_t data[2];
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x45);
    }
    {
        auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
        readTransaction.read(data, 2);
    }
    gyroY = (data[0] << 8) | data[1];
    gyroY = gyroY / gyroscopeSensitivity;
    return gyroY;
}

int16_t MPU6050::getGyroZ(){
    int16_t gyroZ;
    uint8_t data[2];
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x47);
    }
    {
        auto readTransaction = ((hwlib::i2c_bus*)(&bus))->read(address);
        readTransaction.read(data, 2);
    }
    gyroZ = (data[0] << 8) | data[1];
    gyroZ = gyroZ / gyroscopeSensitivity;
    return gyroZ;
}

void MPU6050::resetGyroscope(){
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x68);
        writeTransaction.write(0x04);
    }
}

void MPU6050::resetChip(){
    {
        auto writeTransaction = ((hwlib::i2c_bus*)(&bus))->write(address);
        writeTransaction.write(0x6B);
        writeTransaction.write(0x80);
    }
	hwlib::wait_ms(100);
    gyroscopeSensitivity = 131;
    accelerometerSensitivity = 16384;
}