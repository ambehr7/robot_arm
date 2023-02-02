#include <Servo.h>
Servo s1;
Servo s2;
Servo s3;
Servo s4;
int pos1;
int pos2;
int pos3;
int pos4;
int speedfactor = 15;

void setup() {
  Serial.begin(9600);

  s1.attach(9);
  s2.attach(10);
  s3.attach(6);
  s4.attach(11);
  pos1 = 10; 
  pos2 = 100;
  pos3 = 80;
  pos4 = 10;

  s1.write(pos1);
  delay(200);
  s2.write(pos2);
  delay(200);
  s3.write(pos3);
  delay(200);
  s4.write(pos4);
  delay(200);
}

/*
* moves a single servo to the endposition. Returns the new current position
*/
int makeMove(Servo s, int endpos, int cpos, int speed){
  if(endpos == cpos){
    return cpos;
  }

  if(endpos > cpos){
    for(int i = cpos; i < endpos; i++){
      s.write(i);
      delay(speed);
    }
      return endpos;
  }

  if(endpos < cpos){
    for(int i = cpos; i > endpos; i--){
      s.write(i);
      delay(speed);
    }
    return endpos;
  }

}

/*
format for recieve bytes:
{(servo number 1-4), (move speed 1-9), (pos argument), (pos argument (optional)), (pos argument (optional))}
*/
void loop() {
  char myData[20];
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    byte m = Serial.readBytesUntil('\n', myData, 20);
    myData[m] = '\0';  //insert null charcater
    char snum = myData[0];
    int moveSpeed = speedfactor - atoi(myData[1]);
    //Serial.print(myData);
    //Serial.print("   ");
    char newPos[] = {'0', '0', '0'};
    for(int i = 0; i < 3; i++){
      if(myData[i+2] != '\0'){
        newPos[i] = myData[i+2];
      }
    }

    Serial.print("servo num: ");
    Serial.print(snum);
    Serial.print("      ");
    Serial.print("newPos: ");
    
    int x = atoi(newPos); //converts string to int
    Serial.print(x);
  switch (snum){
    case '1':
      pos1 = makeMove(s1, x, pos1, moveSpeed);
      break;

    case '2':
      pos2 = makeMove(s2, x, pos2, moveSpeed);
      break;

    case '3':
      pos3 = makeMove(s3, x, pos3, moveSpeed);
      break;

    case '4':
      pos4 = makeMove(s4, x, pos4, moveSpeed);
      break;
    
    default:
      break;
  }
  }
}

