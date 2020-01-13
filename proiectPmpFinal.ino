#include <Servo.h>
// Pinii motor 1
#define mpin00 5
#define mpin01 6
// Pinii motor 2
#define mpin10 3
#define mpin11 11

// defines pins numbers
const int trigPin = 9;
const int echoPin = 13;
// defines variables
long duration;
int distance;
int nr = 0;

Servo srv;
void setup() {
  // configurarea pinilor motor ca iesire, initial valoare 0
  digitalWrite(mpin00, 0);
  digitalWrite(mpin01, 0);
  digitalWrite(mpin10, 0);
  digitalWrite(mpin11, 0);
  pinMode (mpin00, OUTPUT);
  pinMode (mpin01, OUTPUT);
  pinMode (mpin10, OUTPUT);
  pinMode (mpin11, OUTPUT);
  // pin LED
  pinMode(13, OUTPUT);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
}
// Funcție pentru controlul unui motor
// Intrare: pinii m1 și m2, direcția și viteza
void StartMotor (int m1, int m2, int forward, int speed)
{

  if (speed == 0) // oprire
  {
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
  }
  else
  {
    if (forward)
    {
      digitalWrite(m2, 0);

      analogWrite(m1, speed); // folosire PWM
    }
    else
    {
      digitalWrite(m1, 0);
      analogWrite(m2, speed);
    }
  }
}
// Funcție de siguranță
// Execută oprire motoare, urmată de delay
void delayStopped(int ms)
{
  StartMotor (mpin00, mpin01, 0, 0);
  StartMotor (mpin10, mpin11, 0, 0);
  delay(ms);
}
// Utilizare servo
// Poziționare în trei unghiuri
// La final, rămâne în mijloc (90 grade)
void playWithServo(int pin)
{

}

void loop() {

  // Senzor miscare

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(500);
  // FATA

  StartMotor (mpin00, mpin01, 1, 45);
  StartMotor (mpin10, mpin11, 1, 45);

  delay (500);
  delayStopped(500);


  digitalWrite(13, 1);
  // Pornirea motorului Servo
  playWithServo(8);

  if (distance <= 30) {
    nr += 1;

    if (nr == 1) {


      StartMotor (mpin00, mpin01, 1, 100);
      StartMotor (mpin10, mpin11, 1, 100);
      delay (500);
      delayStopped(500);

    }
  }


  if (distance <= 30 && nr == 2) {

    Serial.println("Parcheaza");

    // FATA

    StartMotor (mpin00, mpin01, 1, 45);
    StartMotor (mpin10, mpin11, 1, 45);

    delay (500);
    delayStopped(500);

    // LATERAL

    StartMotor (mpin00, mpin01, 1, 50);
    StartMotor (mpin10, mpin11, 0, 50);

    delay (500);
    delayStopped(500);

    // SPATE PUTIN

    StartMotor (mpin00, mpin01, 0, 75);
    StartMotor (mpin10, mpin11, 0, 75);


    delay (500);
    delayStopped(500);

    // LATERAL INAPOi

    StartMotor (mpin00, mpin01, 0, 45);
    StartMotor (mpin10, mpin11, 1, 45);

    delay (500);
    delayStopped(500);

    // PUTIN FATA

    StartMotor (mpin00, mpin01, 1, 25);
    StartMotor (mpin10, mpin11, 1, 25);

    delay (1000);
    delayStopped(1000);

    nr = 0;

  }



}
