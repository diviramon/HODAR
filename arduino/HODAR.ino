/*
 Name:		HODAR.ino
 Created:	10/8/2019 11:27:00 AM
 Author:	dramonprados
*/

#include <TimerOne.h>
#include <LIDARLite_v4LED.h>
#include <LIDARLite_v3HP.h>
#include <LIDARLite.h>
#include <SoftwareServo.h>



LIDARLite myLidarLite; // LIDAR controller
const int stepPin = 3; // Pin to control the steeper, HIGH = ON, LOW = OFF
const int dirPin = 4; // control the stepper direction
SoftwareServo servo; // Servo controller

// Geometric parameters
char s[15]; // string to be sent through serial
int x, y, z; // cartesian coordinates
int r, yawAngle, pitchAngle; // spherical coordinates
int servoAngle; // current angle of the servo
float theta, phi; // for the angle conversion to radians
double step = 1.8 / 16; // by default the motor has a step of 1.8 degrees. However, the mode we run it is 1/16 of the step. 

// Accuracy/speed parameters
int pitch_change = 1; // change in the pitch angle between rounds
int roundsperpitch = 1; // how many 360 rotations per pitch angle
int DELAY_MEASUREMENTS = 0; // delay between measurements, it can be set to zero. This is only used to allowed the plotting to happen 
// in real time. 250 is as fast as you can go, otherwise it will gather data faster than we can plot it and you will see a delay (no data is lost)


// Interrupt parameters
volatile int stepCount = 0;
volatile int roundCount = 0;


// the setup function runs once when you press reset or power the board
void setup() 
{
	// Start serial communication, I find this baud rate to be the best.
	Serial.begin(115200);
	
	// Initiate the communication with the Lidar, we will use I2C communication.
	myLidarLite.begin(0, true);
	myLidarLite.configure(0); 

	// Steeper set up
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	digitalWrite(dirPin, HIGH); // specify the direction 

	// Servo set up
	servo.attach(6); // pin connected to the servo
	servoAngle = 0; // first angle
	servo.write(servoAngle); // start at the top

	// Start the interrupt
	Timer1.initialize();
	Timer1.attachInterrupt(tick, 1000000.0f / (3200*1)); // 3200 is the number of steps in one 360 round
}


void loop()
{
	receive(true); // the Lidar has a measurement correction bias that can be used. The first measurement normally needs it.
	for (int i = 0; i < 99; i++)
		//delayMicroseconds(DELAY_MEASUREMENTS); // testing purposes
		receive(false); 
}

// This is the interrupt function
void tick()
{
	digitalWrite(stepPin, HIGH); 
	//delay(1); // the delay is normally used to control the speed of the step. For us, we want it as fast as possiblle
	digitalWrite(stepPin, LOW);

	stepCount++; 
	if (stepCount >= 3200) // 3200 steps equal to one full turn at the current step size
	{
		stepCount = 0; // reset number of steps
		roundCount++; // increase the number of full 360 rotations
	}
	
}

// Function to retrieve the data from the Lidar and convert from spherical to cartesian
void receive(bool bias)
{
	yawAngle = stepCount * step; // currently the stepper is set to 1/16 of step size
	pitchAngle = 90 - servoAngle; // adjust the servo angle to the true polar angle in spherical

	r = myLidarLite.distance(bias); // retrieve the distance from the lidar
	theta = (float)yawAngle * PI / 180.0f; // cosine and sine require radians
	phi = (float)pitchAngle * PI / 180.0f; // cosine and sine require radians

	sprintf(s, "%d %d %d\n\0", (int)(r * cos(phi) * cos(theta)), (int)(r * cos(phi) * sin(theta)), (int)(r * sin(phi))); // send the x,y,z through serial
	Serial.print(s);

	if (roundCount >= roundsperpitch) // condition to move the servo. Rounds per pitch is how many full 360 rotations we want per servo angle
	{
		servoAngle += pitch_change; // increase the pitch angle
		if (servoAngle > 153) servoAngle = 0; // this would basically mean that we have finished a whole scan and we are starting a new one, in theory it 
											  // should be 180, but the Lidar will hit the frame if we go that low
		servo.write(servoAngle);
		//delay(15);
		roundCount = 0;  // reset the number of round counts at the new servo angle
	}
	servo.refresh(); // this is because we are using an old servo library that does not use timer1 to control the servo. Instead, it just needs to be refreshed
}
