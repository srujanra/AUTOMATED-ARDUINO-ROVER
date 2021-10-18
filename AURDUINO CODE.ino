#include <Servo.h>
Servo servo;

// DC motors right side
#define P1 2                // define pin 2 as for P1 
#define P2 7                // define pin 7 as for P2
#define EN1 8              // define pin 8 as for 1 enable



// DC motors left side
#define P3 4                // define pin 10 as for P3
#define P4 5                // define pin 13 as for P4
#define EN2 9              // define pin 9 as for 2 enable


const int trigPin = 13 ;
const int echoPin = 12 ;

// defining two variable for measuring the distance
long duration;
int distance;



void setup() {

  Serial.begin(9600);        // setup Serial Monitor to display information

  pinMode(P1, OUTPUT);      // define pin as OUTPUT for P1
  pinMode(P2, OUTPUT);      // define pin as OUTPUT for P2
  pinMode(EN1, OUTPUT);   // define pin as OUTPUT for 1EN

  pinMode(P3, OUTPUT);      // define pin as OUTPUT for P3
  pinMode(P4, OUTPUT);      // define pin as OUTPUT for P4
  pinMode(EN2, OUTPUT);   // define pin as OUTPUT for 2EN
  
  pinMode(trigPin, OUTPUT);   // Setting the trigPin as Output pin
  pinMode(echoPin, INPUT);    // Setting the echoPin as Input pin

  servo.attach(10);
  servo.write(115);
  delay(2000);
  
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

}



void loop() {
  int distanceR = 0;
  int distanceL =  0;
  delay(40);
  distance = readPing();
  digitalWrite(trigPin, LOW);                // Making the trigpin as low
  delayMicroseconds(2);                     // delay of 2us
  digitalWrite(trigPin, HIGH);              // making the trigpin high for 10us to send the signal
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);       // reading the echopin which will tell us that how much time the signal takes to come back
  //  distance = duration * 0.034 / 2;         // Calculating the distance and storing in the distance variable

  if (distance > 0 ) {
    digitalWrite(EN1 , 1);            // enable 1 high
    digitalWrite(EN2 , 1);            //enable 2 high
    if (distance <= 25)
    {
      moveStop();
      Serial.println(" movement stopped");
      delay(100);
      moveBackward();
      Serial.println(" moving backward");
      delay(300);
      
      moveStop();    
      Serial.println(" movement stopped");
      delay(200);
      
      distanceR = lookRight();
      Serial.println("looking right");
      delay(200);
      
      distanceL = lookLeft();
      Serial.println("looking left");
      delay(200);
      
      if (distanceR >= distanceL)
      {
        turnRight();
        Serial.println("turing right");
        moveStop();
        Serial.println(" movement stopped");
      }

      else
      {
        turnLeft();
        Serial.println("turing left");
        moveStop();
        Serial.println(" movement stopped");
      }

    }
    else
    {
      moveForward();
      Serial.println("moving forward");
    }
    distance = readPing();

  }


  else {
    Serial.println(" ultrasonic sensor disconnected");
    digitalWrite(EN1 , 0);           // Enable 1 is low
    digitalWrite(EN2 , 0);           // Enable 2 is low
  }


}

int lookRight()
{
  servo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo.write(115);
  return distance;
}

int lookLeft()
{
  servo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo.write(115);
  return distance;
  delay(100);
}


int readPing() {
  delay(70);
  int value = duration * 0.034 / 2;         // Calculating the distance and storing in the distance variable
  return value;
}

void moveStop() {

  digitalWrite(P1, 0);             // send + or HIGH singal to P1
  digitalWrite(P2, 0);              // send - or LOW singal to P2
  digitalWrite(P3, 0);             // send + or HIGH singal to P3
  digitalWrite(P4, 0);              // send - or LOW singal to P4

}


void moveForward() {


  digitalWrite(P1, HIGH);             // send + or HIGH singal to P1
  digitalWrite(P2, LOW);              // send - or LOW singal to P2
  digitalWrite(P3, HIGH);             // send + or HIGH singal to P3
  digitalWrite(P4, LOW);              // send - or LOW singal to P4

}

void moveBackward() {

  digitalWrite(P1, LOW);              // send - or LOW singal to P1
  digitalWrite(P2, HIGH);             // send + or HIGH singal to P2
  digitalWrite(P3, LOW);              // send - or LOW singal to P3
  digitalWrite(P4, HIGH);             // send + or HIGH singal to P4

}

void turnRight() {
  digitalWrite(P1, HIGH);              // send + or HIGH singal to P1
  digitalWrite(P2, LOW);             // send - or LOW singal to P2
  digitalWrite(P3, LOW);              // send - or LOW singal to P3
  digitalWrite(P4, HIGH);             // send + or HIGH singal to P4
  delay(300);
  moveForward();

}

void turnLeft() {

  digitalWrite(P1, LOW);               // send - or LOW singal to P1
  digitalWrite(P2, HIGH);             // send + or HIGH singal to P2
  digitalWrite(P3, HIGH);            // send + or HIGH singal to P3
  digitalWrite(P4, LOW);            // send - or LOW singal to P4

  delay(300);
  moveForward();
}