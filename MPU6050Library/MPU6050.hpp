#ifndef MPU6050_HPP
#define MPU6050_HPP
#include "hwlib.hpp"

/// @file
/// \brief
/// Library for the MPU6050
/// \details
/// This class provides a library containing multiple functions for the MPU3060.
class MPU6050{
private:
    uint8_t address;
    float gyroscopeSensitivity;
    int accelerometerSensitivity;
    hwlib::i2c_bus_bit_banged_scl_sda & bus;

public:
    /// \brief
    /// Initilizes values.
    /// \details
    /// This is the class's constructor which initilizes the chip's address, the i2c bus and the sensitivity of the gyroscope and accelerometer, 
    /// which are set to their default values. 
    MPU6050(uint8_t address, hwlib::i2c_bus_bit_banged_scl_sda & bus):
    address (address),
    gyroscopeSensitivity (131),
    accelerometerSensitivity (16384),
    bus (bus)
    {}

    /// \brief
    /// Wakes up the chip.
    /// \details
    /// This function wakes up the chip so all other functions can be used.
    void wakeUp();

    /// \brief
    /// Returns the chip's address.
    /// \details
    /// This function returns the adress of the chip. This is either 0x68 when AD0 is set to low or 0x69 when AD0 is set to high.
    int whoAmI();

    /// \brief
    /// Reads a register.
    /// \details
    /// This function will read the value of the register that it is given.
    uint8_t readRegister(uint8_t registerAdress);

    /// \brief
    /// sets the accelerometer sensitivity.
    /// \details
    /// This function sets the sensitivity of the accelerometer depending on what full scale range it is given.
    /// The scaling goes like this: 0 = ±2g, 1 = ±4g, 2 = ±8g, 3 = ±16g. 
    void setAccelerometerSensitivity(uint8_t fullScaleRange);

    /// \brief
    /// sets the Gyroscope sensitivity.
    /// \details
    /// This function sets the sensitivity of the Gyroscope depending on what full scale range it is given.
    /// The scaling goes like this: 0 = ±250°/s, 1 = ±500°/s, 2 = ±1000°/s, 3 = ±2000°/s. 
    void setGyroscopeSensitivity(uint8_t fullScaleRange);

    /// \brief
    /// Returns the temperature.
    /// \details
    /// This function returns the temperature in degrees °C.
    int16_t getTemperature();

    /// \brief
    /// Resets the temperature.
    /// \details
    /// This function resests the temperature sensor. 
    void resetTemperature();

    /// \brief
    /// Returns the accelerometer's X value.
    /// \details
    /// This function returns the accelerometer's X value in g *10^3.
    int16_t getAccellerationX();

    /// \brief
    /// Returns the accelerometer's Y value.
    /// \details
    /// This function returns the accelerometer's Y value in g *10^3.
    int16_t getAccellerationY();

    /// \brief
    /// Returns the accelerometer's Z value.
    /// \details
    /// This function returns the accelerometer's Z value in g *10^3.
    int16_t getAccellerationZ();

    /// \brief
    /// Resets the accelerometer.
    /// \details
    /// This function resests the accelerometer. 
    void resetAccelerometer();

    /// \brief
    /// Returns the gyroscope's X value.
    /// \details
    /// This function returns the gyroscope's X value in °/s.
    int16_t getGyroX();

    /// \brief
    /// Returns the gyroscope's Y value.
    /// \details
    /// This function returns the gyroscope's Y value in °/s.
    int16_t getGyroY();

    /// \brief
    /// Returns the gyroscope's Z value.
    /// \details
    /// This function returns the gyroscope's Z value in °/s.
    int16_t getGyroZ();

    /// \brief
    /// Resets the gyroscope.
    /// \details
    /// This function resests the gyroscope. 
    void resetGyroscope();

    /// \brief
    /// Resets chip.
    /// \details
    /// This function will reset the chip.
    void resetChip();
};

#endif