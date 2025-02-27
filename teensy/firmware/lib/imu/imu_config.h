#ifndef _IMU_CONFIG_H_
#define _IMU_CONFIG_H_

#include "I2Cdev.h"

#define G_TO_ACCEL 9.81
#define MGAUSS_TO_UTESLA 0.1
#define UTESLA_TO_TESLA 0.000001

#ifdef USE_GY85_IMU
    #include "ADXL345.h"
    #include "ITG3200.h"
    #include "HMC5883L.h"

    #define ACCEL_SCALE 1 / 256 // LSB/g
    #define GYRO_SCALE 1 / 14.375 // LSB/(deg/s)
    #define MAG_SCALE 0.92 * MGAUSS_TO_UTESLA // uT/LSB

    ADXL345 accelerometer;
    ITG3200 gyroscope;
    HMC5883L magnetometer;
#endif

#ifdef USE_MPU6050_IMU
    #include "MPU6050.h"
    #include "fake_mag.h"

    #define ACCEL_SCALE 1 / 16384 // LSB/g
    #define GYRO_SCALE 1 / 131 // LSB/(deg/s)
    #define MAG_SCALE 0.3 // uT/LSB
    
    MPU6050 accelerometer;
    MPU6050 gyroscope;    
    FakeMag magnetometer;
#endif

#ifdef USE_MPU9150_IMU
    #include "MPU9150.h"

    #define ACCEL_SCALE 1 / 16384 // LSB/g
    #define GYRO_SCALE 1 / 131 // LSB/(deg/s)
    #define MAG_SCALE 0.3 // uT/LSB
    
    MPU9150 accelerometer;
    MPU9150 gyroscope;    
    MPU9150 magnetometer;
#endif

#ifdef USE_MPU9250_IMU
    #include "MPU9250.h"

    #define ACCEL_SCALE 1 / 16384 // LSB/g
    #define GYRO_SCALE 1 / 131 // LSB/(deg/s)
    #define MAG_SCALE 0.6 // uT/LSB
    
    MPU9250 accelerometer;
    MPU9250 gyroscope;    
    MPU9250 magnetometer;
#endif

#ifdef USE_BNO055
    #include "Adafruit_Sensor.h"
    #include "Adafruit_BNO055.h"
    #include "utility/imumaths.h"

    //#include "fake_mag.h"

    #define ACCEL_SCALE 1000 // LSB/g           1 mg = 1 LSB => 1g = 1000 LSB
    #define GYRO_SCALE 0.0625 // LSB/(deg/s)    1 Dps = 16 LSB (Datasheet 3.6.4.3)
    #define MAG_SCALE 0.0625 // uT/LSB          1 uT = 16 LSB

    //#define ACC_UNIT (1)    // (0): m/s^2   (1): mg
    //#define GYR_UNIT (1)    // (0): degree/s   (1): rad/s

    Adafruit_BNO055 bno;
    //FakeMag magnetometer;
    //write8(BNO055_PAGE_ID_ADDR, 0);     // Select relevant register page

    // Change the default units for acc and gyro
    //uint8_t unitsel = (uint8_t) ((GYR_UNIT << 1)
    //                | (ACC_UNIT << 0));

    //write8(0x3B, unitsel);

#endif

#endif

//ADXL345 https://www.sparkfun.com/datasheets/Sensors/Accelerometer/ADXL345.pdf
//HMC8553L https://cdn-shop.adafruit.com/datasheets/HMC5883L_3-Axis_Digital_Compass_IC.pdf
//ITG320 https://www.sparkfun.com/datasheets/Sensors/Gyro/PS-ITG-3200-00-01.4.pdf


//MPU9150 https://www.invensense.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf
//MPU9250 https://www.invensense.com/wp-content/uploads/2015/02/MPU-9150-Datasheet.pdf
//MPU6050 https://store.invensense.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf

//http://www.sureshjoshi.com/embedded/invensense-imus-what-to-know/
//https://stackoverflow.com/questions/19161872/meaning-of-lsb-unit-and-unit-lsb
