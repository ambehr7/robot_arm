#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;

void setup() {
  Serial.begin(9600);
  s1.attach(9);
  s2.attach(10);
  s3.attach(11);
  s4.attach(6);

  s1.write(50);
  delay(200);
  s2.write(50);
  delay(200);
  s3.write(50);
  delay(200);
  s4.write(50);
  delay(200);
}

void loop() {
    for(int i = 50; i < 100; i++){
      s1.write(i);
      delay(5);
  }

  for(int i = 100; i > 50; i--){
      s1.write(i);
      delay(5);
    }

  for(int i = 50; i < 100; i++){
      s2.write(i);
      delay(5);
  }

  for(int i = 100; i > 50; i--){
      s2.write(i);
      delay(5);
    }
  for(int i = 50; i < 100; i++){
      s3.write(i);
      delay(5);
  }

  for(int i = 100; i > 50; i--){
      s3.write(i);
      delay(5);
    }

    for(int i = 50; i < 100; i++){
      s4.write(i);
      delay(5);
  }

  for(int i = 100; i > 50; i--){
      s4.write(i);
      delay(5);
    }
}
