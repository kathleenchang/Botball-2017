#include "legobotConstants.h"
#include "legobotFunctions.h"
#include "legobotVision.h"


void tribbleCollectTest() {
	printf("collecting test");
	legobotInit();
	printf("collecting test");
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	mav(SPINNER_MOTOR, 500);
	
	thread dipstickThread;
	dipstickThread = thread_create(dipstickDoesShit);
	thread_start(dipstickThread);
	
	msleep(4000);
	
	halt();
	turn(-90.0);
	
	motor(RIGHT_MOTOR, 40*1.05);
	motor(LEFT_MOTOR, 40);
	
	msleep(5000);
	
	ao();
	msleep(1000);
	thread_destroy(dipstickThread);
}

int main() {
	legobotInit();
	
	printf("Press side button to end, A button to test dist, B button to test turn, C button to run longer test");
	while(1) {
		if (a_button()) {
			
			enable_servo(HANGER_SERVO);
			set_servo_position(HANGER_SERVO,HANGER_FORWARD);
			msleep(1500);
			moveToDist(NORMAL_SPEED,-25);
			msleep(100);
			pivotOnRight(NORMAL_SPEED,5);
			msleep(1000);
			raiseArm();
			msleep(500);
			moveArm(-90);
			moveToDist(NORMAL_SPEED,26);
			msleep(100);
			raiseArm();
			msleep(200);
			moveArm(-100);
			msleep(100);
			set_servo_position(HANGER_SERVO,HANGER_BACK);
			msleep(1000);
			

			
			
			//arcToWallAlign(NORMAL_SPEED, 1,1);
			
			//pivotOnLeft(NORMAL_SPEED, 45);
			//pivotOnRight(NORMAL_SPEED, 45);
			//pivotOnLeft(NORMAL_SPEED, -45);
			//pivotOnRight(NORMAL_SPEED, -45);
		}
		else if (b_button()) {
			//arcToWallAlign(NORMAL_SPEED, 1, 1);
			cameraInitialize();
			//while(1) {
				moveToDistWithKicker(NORMAL_SPEED, 100, 1);
				//camera_update();
				//camera_update();
				//printf("\n%d, size: %d",getRightMostBlock(2), get_object_area(getRightMostBlock(2), 0));
				//msleep(5);
			//}
			/*enable_servo(HANGER_SERVO);
			set_servo_position(HANGER_SERVO,HANGER_BACK);
			msleep(2000);
			moveToDist(NORMAL_SPEED,-13);
			raiseArm();
			msleep(2000);
			pivotOnRight(NORMAL_SPEED,5);
			moveToDist(NORMAL_SPEED,15);
			msleep(1000);
			set_servo_position(HANGER_SERVO,HANGER_FORWARD);
			msleep(200);
			pivotOnRight(NORMAL_SPEED,10);
			msleep(200);
			moveToDist(NORMAL_SPEED,-13);*/
			
		}
		else if (c_button()) {
			cameraInitialize();
			thread spinnerThread = thread_create(spinnerStart);
			thread_start(spinnerThread);
			//arcToWallAlign(NORMAL_SPEED+10, 1, 1);
			//arcToTouch(NORMAL_SPEED, 1, 1);
			//pivotOnRightTillLeftTouch(NORMAL_SPEED, 1);
			
			
			//wall align
			moveToTouch(NORMAL_SPEED); 
			pivotOnLeft(NORMAL_SPEED, -60);
			moveToDist(NORMAL_SPEED, -5);
			pivotOnRight(NORMAL_SPEED, -60);
			moveToDist(NORMAL_SPEED,-9);
			turnTest(-87.5);
			
			//move to black tape
			//moveToDistWithDipstick(SLOW_SPEED, 46);
			moveToDistWithKickerAndDipstick(NORMAL_SPEED, 46, 1);
			//turn to center of board
			turnTest(-87.5);
			//move to center of board
			moveToDistWithDipstick(SLOW_SPEED, 68);
			//turnt to rack
			turnTest(88.4);
			msleep(1000);
			raiseArm();
			msleep(500);
			setHangerClawPosition(HANGER_UP);
			moveToWallAlign(NORMAL_SPEED);
			msleep(500);
			setHangerClawPosition(HANGER_FORWARD);
			msleep(500);
			thread_destroy(spinnerThread);
			off(SPINNER_MOTOR);
			moveArm(-100);
			msleep(100);
			moveToDist(NORMAL_SPEED, -5);
			msleep(100);
			pivotOnLeft(NORMAL_SPEED, -90);
			moveToDist(NORMAL_SPEED, 5);
			resetArm();
			//pivotOnLeft(NORMAL_SPEED, 90);
			//turnTest(-87.5);
			
			moveToDist(NORMAL_SPEED, -20);
			turnTest(-90);
			moveToDist(NORMAL_SPEED,30);
			turnTest(90);
			moveToDist(NORMAL_SPEED, 20);
			setHangerClawPosition(HANGER_UP);
			setHangerClawPosition(HANGER_FORWARD);
			moveToDist(NORMAL_SPEED, -15);
			raiseArm();
			msleep(500);
			moveArm(-90);
			moveToDist(NORMAL_SPEED, 15);
			
			raiseArm();
			msleep(500);
			moveArm(90);
			
			
			
			
			
			
			
			
			//moveToDist(NORMAL_SPEED,-5);
			//pivotOnleft(NORMAL_SPEED, -30);
			//pivotOnRight(NORMAL_SPEED, 90);
			
		
		}
		msleep(100);
	}
	
}

void turnTest(double degrees) {
	clear_motor_position_counter(LEFT_MOTOR);
	
	double ticks = degrees * TICKS_PER_DEGREE;
	//everything is calibrated around left wheel
	if (ticks < 0) {
		motor(LEFT_MOTOR, -1*NORMAL_SPEED);
		motor(RIGHT_MOTOR, NORMAL_SPEED);
		while (get_motor_position_counter(LEFT_MOTOR) > ticks) {
			msleep(30);
		}
	}
	else {
		motor(LEFT_MOTOR, NORMAL_SPEED);
		motor(RIGHT_MOTOR, -1*NORMAL_SPEED);
		while (get_motor_position_counter(LEFT_MOTOR) < ticks) {
			msleep(30);
		}
	}
	
	halt();
}
