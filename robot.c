#pragma config(Sensor, in1,    shoulderPot,    sensorPotentiometer)
#pragma config(Sensor, dgtl1,  baseEnc,        sensorQuadEncoder)
#pragma config(Motor,  port2,           base,          tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           shoulder,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           elbow,         tmotorServoStandard, openLoop)
#pragma config(Motor,  port5,           wrist,         tmotorServoStandard, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

const int BASE_PLATE = 0;
const int BASE_BREAD = 0;
const int BASE_GRIDDLE = 600;
int baseTarget = 0;
bool coast = false;
bool baseReached = false;
task baseControl()
{
	while(true)
	{
		int curr = SensorValue[baseEnc];
		baseReached = abs(curr - baseTarget) < 20;
		if(!baseReached)
		{
			motor[base] = 60 * sgn(curr - baseTarget);
		}
		else
		{
			if(coast)
			{
				motor[base] = 50;
				wait1Msec(500);
				motor[base] = 20;
				wait1Msec(500);
				baseTarget = SensorValue[baseEnc];
				coast = false;
			}
			motor[base] = 0;
		}
		EndTimeSlice();
	}
}

const int SHOULDER_DOWN_LOW = 2700;
const int SHOULDER_DOWN = 2400;
const int SHOULDER_UP = 2050;
int shoulderSpeed = 35;
int shoulderTarget = SHOULDER_UP;
bool shoulderReached = false;
task shoulderControl()
{
	while(true)
	{
		int curr = SensorValue[shoulderPot];
		shoulderReached = abs(curr - shoulderTarget) < 50;
		if(!shoulderReached)
		{
			motor[shoulder] = shoulderSpeed * sgn(curr - shoulderTarget);
		}
		else
		{
			motor[shoulder] = 0;
		}
		EndTimeSlice();
	}
}

const int ELBOW_MAX = 100;
const int ELBOW_MID = 0;
const int ELBOW_MIN = -80;
int elbowTarget = ELBOW_MID;
bool elbowReached = false;
task elbowControl()
{
	while(true)
	{
		int curr = motor[elbow];
		elbowReached = abs(curr - elbowTarget) <= 5;
		if(!elbowReached)
		{
			motor[elbow] += 5 * sgn(curr - elbowTarget);
		}
		EndTimeSlice();
	}
}

const int WRIST_MAX = 40;
const int WRIST_MID = 0;
const int WRIST_MIN = -50;
int wristTarget = WRIST_MID;
bool wristReached = false;
task wristControl()
{
	while(true)
	{
		waitUntil(!wristReached);
		int curr = motor[wrist];
		while (abs(curr - wristTarget) > 5)
		{
			curr += 2 * sgn(curr - wristTarget);
			wait1Msec(100);
		}
		wristReached = true;
		EndTimeSlice();
	}
}

void setBase(int target)
{
	baseTarget = target;
	wait1Msec(100);
	waitUntil(baseReached);
}


void setShoulder(int target, int speed = 35, int timeout = 10000)
{
	shoulderSpeed = speed
	shoulderTarget = target;
	wait1Msec(100);
	clearTimer(timer1);
	waitUntil(shoulderReached || time1[timer1] > timeout);
	shoulderReached = true;
}

void setElbow(int target)
{
	elbowTarget = target;
	wait1Msec(100);
	waitUntil(elbowReached);
}

void setWrist(int target)
{
	wristReached = false;
	wristTarget = target;
	waitUntil(wristReached);
}

task main()
{
	//DROP BREAD
	//baseTarget = BASE_PLATE - 150;
	/*SensorValue[baseEnc] = -150;
	startTask(baseControl);
	startTask(shoulderControl);
	waitUntil(shoulderReached && baseReached);
	wait1Msec(5000);
	//We are now reset in front of the plate
	motor[wrist] = 20;
	//Angle spatula down to pick up bread
	wait1Msec(500);
	motor[elbow] = -25;
	setShoulder(2400, 10, 1000);
	//Arm moves down, wedged under bread
	wait1Msec(1250);
	//Lift bread onto spatula
	motor[elbow] = -10;
	setShoulder(2600, 35, 500);
	wait1Msec(500);
	motor[elbow] = 50;
	setShoulder(2800, 25, 500);
	wait1Msec(250);
	motor[wrist] = 40;
	motor[elbow] = 40;
	setShoulder(2400, 25);
	wait1Msec(500);
	motor[wrist] = 60;
	//Bread is now secured on spatula
	setShoulder(SHOULDER_UP);
	//Lift higher in prep for moving
	wait1Msec(500);
	coast = true;
	setBase(BASE_GRIDDLE);
	//Gently drive over to griddle
	wait1Msec(500);
	setShoulder(2350, 20);
	motor[wrist] = -20;
	wait1Msec(500);
	setShoulder(2200, 20);
	motor[wrist] = -50;
	wait1Msec(250);
	setShoulder(SHOULDER_UP, 40, 1000);
	motor[wrist] = -70;
	wait1Msec(3500);*/
	//END DROP BREAD
	//FLIP BREAD
	/*shoulderTarget = SHOULDER_UP;
	startTask(shoulderControl);
	setShoulder(SHOULDER_UP);
	wait1Msec(1000);
	//Realign to be able to pick up bread slice
	motor[wrist] = -25;
	wait1Msec(250);
	motor[elbow] = 30;
	wait1Msec(250);
	motor[wrist] = -50;
	motor[elbow] = 20;
	//Nudge in slightly
	wait1Msec(250);
	setShoulder(2400, 20, 500);
	wait1Msec(250);
	motor[elbow] = 35;
	setShoulder(2400, 20, 500);
	wait1Msec(250);
	motor[elbow] = 50;
	//Get under bread
	motor[wrist] = -20;
	wait1Msec(500);
	motor[elbow] = 60;
	setShoulder(2550);
	//Slight extra grip under bread
	wait1Msec(500);
	stopTask(shoulderControl);
	//Stop for flick
	motor[wrist] = 20;
	motor[shoulder] = 127;
	wait1Msec(150);
	motor[shoulder] = 0;
	//Flick bread*/
	//END FLIP BREAD
	//PLATE BREAD
	shoulderTarget = SHOULDER_UP;
	SensorValue[baseEnc] = 0;
	baseTarget = SensorValue[baseEnc];
	startTask(shoulderControl);
	startTask(baseControl);
	wait1Msec(5000);
	motor[elbow] = -40;
	wait1Msec(500);
	motor[elbow] = -70;
	wait1Msec(1500);
	int shoulder_move[] = {2050, 2100, 2150, 2250, 2350, 2450, 2550, 2650};
	int elbow_move[] = {-70, -50, -30, -10, 20, 40, 60, 80};
	for(int j = 0; j < 8; j++)
	{
		setShoulder(shoulder_move[j]);
		motor[elbow] = elbow_move[j];
		wait1Msec(100);
	}
	wait1Msec(1500);
	motor[wrist] = 20;
	setShoulder(2400, 25);
	wait1Msec(500);
	wait1Msec(250);
	setShoulder(SHOULDER_UP);
	wait1Msec(500);
	motor[elbow] = 40;
	motor[wrist] = 35;
	wait1Msec(500);
	motor[elbow] = 0;
	motor[wrist] = 50;
	wait1Msec(1500);
	coast = true;
	SensorValue[baseEnc] = 0;
	setBase(-BASE_GRIDDLE + 100);
	wait1Msec(500);
	motor[elbow] = -40;
	wait1Msec(500);
	motor[wrist] = -50;
	waitUntil(false);
}
