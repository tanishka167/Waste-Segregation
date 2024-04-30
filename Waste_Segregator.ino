#include <Servo.h>

const int rainSensorPin = A0;    // Rain sensor connected to analog pin A0
const int ledPin = 13;           // LED connected to digital pin 13
const int servoPin = 9;          // Servo motor connected to digital pin 9
const int trigPin = 5;           // Ultrasonic sensor trigger pin
const int echoPin = 6;           // Ultrasonic sensor echo pin

Servo myservo; // Create a servo object

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(servoPin); // Attach the servo to the specified pin
  Serial.begin(9600);
}

float getDistanceUltrasonic() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2;  // Calculate distance in centimeters
  return distance;
}

void loop() {
  int rainValue = analogRead(rainSensorPin); // Read analog value from rain sensor
  float ultrasonicDistance = getDistanceUltrasonic();  // Get distance from ultrasonic sensor

  Serial.print("Rain Sensor Value: ");
  Serial.println(rainValue);
  Serial.print("Ultrasonic Distance: ");
  Serial.println(ultrasonicDistance);

  int rainThreshold = 500; // Adjust this threshold based on your rain sensor readings
  
  if (ultrasonicDistance < 7 && ultrasonicDistance >2) {
    if (rainValue > rainThreshold && (ultrasonicDistance<7 || ultrasonicDistance>2)) {
      digitalWrite(ledPin, HIGH);
      myservo.write(60); // Move servo to 70 degrees for wet condition
      delay(5000); // Wait for 5 seconds
    } if(rainValue < rainThreshold){
      digitalWrite(ledPin, LOW); // Turn off LED for dry condition
      myservo.write(180); // Move servo to 120 degrees for dry condition
      delay(5000); // Wait for 5 seconds
    
  }} 
  else {
    digitalWrite(ledPin, LOW); // Turn off LED if no rain detected
    myservo.write(90); // Move servo to 90 degrees for normal condition
    delay(5000);
  }
}
