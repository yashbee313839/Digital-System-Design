const int enAL = 6;
const int enBR = 9;
const int in2 = 5;
const int in3 = 7;

void moveBot(int left, int right, int del){
  if (left < 0){
    digitalWrite(in2, HIGH);
  }
  else{
    digitalWrite(in2, LOW);
  }
  if (right < 0){
    digitalWrite(in3, LOW);
  }
  else{
    digitalWrite(in3, HIGH);
  }
  int sL = abs(left);
  int sR = abs(right);
  analogWrite(enAL, sL);
  analogWrite(enBR, sR);    
  if (del) delay(del);
}

void setup(){
  pinMode(enAL, OUTPUT);
  pinMode(enBR, OUTPUT);  
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);     
}

void loop(){
  moveBot(255, 255, 1000);
  moveBot(-255, 255, 2500);
  moveBot(255, -255, 2500);
  moveBot(-255, -255, 1000);    
}


