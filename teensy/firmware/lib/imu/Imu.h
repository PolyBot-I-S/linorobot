#ifndef _IMU2_H_
#define _IMU2_H_

#include "I2Cdev.h"
#include "imu_config.h"

#include <Wire.h>
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"

bool initIMU()
{
    Wire.begin();
    bool ret;
    
    #ifndef USE_BNO055
        accelerometer.initialize();
        ret = accelerometer.testConnection();
        if(!ret)
            return false;

        gyroscope.initialize();
        ret = gyroscope.testConnection();
        if(!ret)
            return false;
    
        magnetometer.initialize();
        ret = magnetometer.testConnection();
        if(!ret)
            return false;
    #else

        bno = Adafruit_BNO055(55, 0x28);

        ret = bno.begin();
        if(!ret)
            return false;
    #endif

    return true;
}

geometry_msgs::Vector3 readAccelerometer()
{
    geometry_msgs::Vector3 accel;

    #ifndef USE_BNO055
        int16_t ax, ay, az;
        
        accelerometer.getAcceleration(&ax, &ay, &az);

        accel.x = ax * (double) ACCEL_SCALE * G_TO_ACCEL;
        accel.y = ay * (double) ACCEL_SCALE * G_TO_ACCEL;
        accel.z = az * (double) ACCEL_SCALE * G_TO_ACCEL;
    #else

        sensors_event_t accelerometer;
        bno.getEvent(&accelerometer, Adafruit_BNO055::VECTOR_LINEARACCEL);
        //bno.getEvent(&accelerometer, Adafruit_BNO055::VECTOR_ACCELEROMETER);

         //accel.x = ((&accelerometer)->acceleration.x) * (double) ACCEL_SCALE * G_TO_ACCEL;
        //accel.x = ((&accelerometer)->acceleration.x) * (double) ACCEL_SCALE;
        //accel.y = ((&accelerometer)->acceleration.y) * (double) ACCEL_SCALE;
        //accel.z = ((&accelerometer)->acceleration.z) * (double) ACCEL_SCALE;
       accel.x = ((&accelerometer)->acceleration.x);
       accel.y = ((&accelerometer)->acceleration.y);
       accel.z = ((&accelerometer)->acceleration.z);
    #endif

    return accel;
}

geometry_msgs::Vector3 readGyroscope()
{
    geometry_msgs::Vector3 gyroscope;
    
    #ifndef USE_BNO055
        int16_t gx, gy, gz;

        gyroscope.getRotation(&gx, &gy, &gz);

        gyroscope.x = gx * (double) GYRO_SCALE * DEG_TO_RAD;
        gyroscope.y = gy * (double) GYRO_SCALE * DEG_TO_RAD;
        gyroscope.z = gz * (double) GYRO_SCALE * DEG_TO_RAD;
    #else
        sensors_event_t angularVelocity;
        bno.getEvent(&angularVelocity, Adafruit_BNO055::VECTOR_GYROSCOPE);

        //gyroscope.x = ((&angularVelocity)->gyro.x) * (double) GYRO_SCALE;
        //gyroscope.y = ((&angularVelocity)->gyro.y) * (double) GYRO_SCALE;
        //gyroscope.z = ((&angularVelocity)->gyro.z) * (double) GYRO_SCALE;

       gyroscope.x = ((&angularVelocity)->gyro.x);
       gyroscope.y = ((&angularVelocity)->gyro.y);
       gyroscope.z = ((&angularVelocity)->gyro.z);
	
    #endif


    return gyroscope;
}

geometry_msgs::Vector3 readMagnetometer()
{
    geometry_msgs::Vector3 mag;

    #ifndef USE_BNO055
        int16_t mx, my, mz;

        magnetometer.getHeading(&mx, &my, &mz);

        mag.x = mx * (double) MAG_SCALE * UTESLA_TO_TESLA;
        mag.y = my * (double) MAG_SCALE * UTESLA_TO_TESLA;
        mag.z = mz * (double) MAG_SCALE * UTESLA_TO_TESLA;
    
    #else
	sensors_event_t magnetometerData;
	bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);

	//mag.x = ((&magnetometerData)->magnetic.x) * (double) MAG_SCALE * UTESLA_TO_TESLA;
	//mag.y = ((&magnetometerData)->magnetic.y) * (double) MAG_SCALE * UTESLA_TO_TESLA;
	//mag.z = ((&magnetometerData)->magnetic.z) * (double) MAG_SCALE * UTESLA_TO_TESLA;

	mag.x = ((&magnetometerData)->magnetic.x) * UTESLA_TO_TESLA;
	mag.y = ((&magnetometerData)->magnetic.y) * UTESLA_TO_TESLA;
	mag.z = ((&magnetometerData)->magnetic.z) * UTESLA_TO_TESLA;
    #endif

    return mag;
}

#ifdef QUAT
geometry_msgs::Quaternion readQuaternion()
{
    geometry_msgs::Quaternion q;

    imu::Quaternion quat = bno.getQuat();

    q.x = quat.x();
    q.y = quat.y();
    q.z = quat.z();
    q.w = quat.w();

    return q;    
}
#endif

#endif
