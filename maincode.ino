#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define x_up 3
#define x_down 5
#define y_up 6
#define  y_down 9
#define z_  10
float x , y , z;


Adafruit_ADXL345_Unified accel (54321);
 void alarmming()
 {
 
  for (int i = 200; i <= 3000; i = i + 10) {
    tone(9, i);
    delay(10);
  }
  for (int i = 3000; i >= 200; i = i - 10) {
    tone(9, i);
    delay(10);
 
 }

 }
void setup()
{
   pinMode(A2,OUTPUT);
  pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
  Serial.begin(9600);
  Serial.println("Accelerometer Test"); Serial.println("");
  pinMode(z_ , 1);
  if (!accel.begin())
  {
    Serial.println(" no ADXL345 detected ... Check your wiring!");
     Serial.println(" Waiting ....");
    delay(2000);
    setup();
  }
  accel.setRange(ADXL345_RANGE_16_G);
  accel.setDataRate(ADXL345_DATARATE_25_HZ);
}

void loop(void)
{
  
  sensors_event_t event;
  accel.getEvent(&event);

  
  x = event.acceleration.x;
  y = event.acceleration.y;
  z = event.acceleration.z;
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  "); Serial.println("m/s^2 ");
  if (z > -11 && z < -9)
  {
    digitalWrite(z_ , 1);
  }
  else
  {
    digitalWrite(z_ , 0);
  }
  if (x > 0)
  {
    x = map(x, 0, 11, 0, 255);
    analogWrite(x_up , x);

  }
  else if (x < 0)
  {

    x = map(x, 0, -10, 0, 255);
    analogWrite(x_down , x);
  }
  if (y < 0)
  {
    y *= -1;
    y = map(y , 0, 10, 0, 255);
    analogWrite(y_down , y);
  }
  else if ( y > 0)
  {
    y = map(y , 0 , 10 , 0, 255);
    analogWrite(y_up , y);
  }


 if (event.acceleration.x<=1 || event.acceleration.x>=-1 || event.acceleration.y<=1    || event.acceleration.y>=-1 )
  {
      digitalWrite(A2,1); analogWrite(A3,600);  digitalWrite(9,1);  digitalWrite(8,1);  analogWrite(A1,600);
  } 
  if (event.acceleration.x>=2)
  {
    analogWrite(A3,700); analogWrite(A1,0); digitalWrite(A2,0);  digitalWrite(9,0);  digitalWrite(8,0);
  }
 if (event.acceleration.x<=-2)
  {
      analogWrite(A3,0); analogWrite(A1,0); digitalWrite(A2,1);  digitalWrite(9,0);  digitalWrite(8,0);
  }

  if (event.acceleration.y>=2)
  {
    analogWrite(A3,0); analogWrite(A1,0); digitalWrite(A2,0);  digitalWrite(9,0);  digitalWrite(8,1);
  }
 if (event.acceleration.y<=-2)
  {
      analogWrite(A3,0); analogWrite(A1,0); digitalWrite(A2,0);  digitalWrite(9,1);  digitalWrite(8,0);
  }



}
  
