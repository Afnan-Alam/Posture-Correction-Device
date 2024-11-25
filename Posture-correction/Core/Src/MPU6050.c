#include <MPU6050.h>
#include <main.h>
#include <stdio.h>
#include <math.h>

extern I2C_HandleTypeDef hi2c1;

void MPU6050_init(){
	HAL_StatusTypeDef ret = HAL_I2C_IsDeviceReady(&hi2c1, (DEVICE_ADDRESS <<1) +0, 1, 100);
	  if (ret == HAL_OK){
		  printf("The device is ready \n");
	  }
	  else{
		  printf("Device is not ready \n");
	  }

	  uint8_t tempdata= FS_GYRO_500;
	   ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) +0, REG_CONFIG_GYRO, 1, &tempdata, 1, 100);
	    if (ret == HAL_OK){
	  	  printf("Writing to register 27 \n");
	    }
	    else{
	  	  printf("Failed writing to register 27 \n");
	    }

		   tempdata= FS_ACC_2G;
		   ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) +0, REG_CONFIG_ACC, 1, &tempdata, 1, 100);
		    if (ret == HAL_OK){
		  	  printf("Writing to register 28 \n");
		    }
		    else{
		  	  printf("Failed writing to register 28 \n");
		    }

		    tempdata= 0;
		   ret = HAL_I2C_Mem_Write(&hi2c1, (DEVICE_ADDRESS <<1) +0, REG_USR_CTRL, 1, &tempdata, 1, 100);
			if (ret == HAL_OK){
			  printf("Exiting from sleep mode \n");
			}
			else{
			  printf("Failed to exit from sleep mode 28 \n");
			}

}

float MPU6050_read(){
	uint8_t dataX[2];
	int16_t x_acc;
	float sensScale = 16384.0;


	uint8_t data[6];
	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS <<1) +0, 0x3b, 1, data, 6, 100);
	int16_t Accel_X_RAW = (int16_t)(data[0] << 8 | data [1]);
	int16_t	Accel_Y_RAW = (int16_t)(data[2] << 8 | data [3]);
	int16_t	Accel_Z_RAW = (int16_t)(data[4] << 8 | data [5]);

	float	Ax = (float)Accel_X_RAW/16384.0;
	float	Ay = (float)Accel_Y_RAW/16384.0;
	float	Az = (float)Accel_Z_RAW/16384.0;

//	printf("\nX axis acceleration: %f \n", Ax);
//	printf("\nY axis acceleration: %f \n", Ay);
//	printf("\nZ axis acceleration: %f \n", Az);
	
//	float xzMag = sqrt(Ax*Ax + Az*Az);
//	float angle_radian = atan2(xzMag, Ay);
//	float angle_degree = -angle_radian * (180.0/M_PI);

	// CHANGE FORMULA TO DETECT ANGLE ON OHTER PLANE
	float  xyMag = sqrt(Ax*Ax + Ay*Ay);
	float angle_radian = atan2(xyMag, Az);
	float angle_degree = -angle_radian* (180.0/M_PI) + 90;

	printf("\nDegree: %f \n", angle_degree);
	return angle_degree;

//	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS <<1) +0, 0x3b, 1, dataX, 2, 100);
//
//	x_acc = ((int16_t) dataX[0] << 8) + dataX[1];
//	int16_t x_accG =  x_acc * sensScale;
//	printf("\nX axis acceleration: %d \n", x_accG);
//
//
//
//	uint8_t dataY[2];
//	int16_t y_acc;
//
//	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS <<1) +0, 0x3d, 1, dataY, 2, 100);
//
//	y_acc = ((int16_t) dataY[0] << 8) + dataY[1];
//	float y_accG =  y_acc * sensScale;
//	printf("\nY axis acceleration: %d \n", y_accG);
//
//
//	uint8_t dataZ[2];
//	int16_t z_acc;
//
//	HAL_I2C_Mem_Read(&hi2c1, (DEVICE_ADDRESS <<1) +0, 0x3f, 1, dataZ, 2, 100);
//
//	z_acc = ((int16_t) dataZ[0] << 8) + dataZ[1];
//	float z_accG =  z_acc / sensScale;
//	printf("\nZ axis acceleration: %d \n", z_accG);

}


