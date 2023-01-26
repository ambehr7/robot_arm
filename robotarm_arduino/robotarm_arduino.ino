#include <Servo.h>
Servo s;
int pos;

void setup() {
  Serial.begin(9600);
  s.attach(9);
  pos = 0;
  s.write(pos);
}

void loop() {
  char myData[20];
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    byte m = Serial.readBytesUntil('\n', myData, 20);
    myData[m] = '\0';  //insert null charcater
    int x = atoi(myData); //converts string to int
    Serial.println(x);
    if(x >= 0 && x =< 180){
      s.write(x);
    }
  }
}
