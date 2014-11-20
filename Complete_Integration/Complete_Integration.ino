#include <Servo.h> 
#include <LiquidCrystal.h>
int encoderPin1 = 3;
int encoderPin2 = 2;

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

Servo myservo;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;

long lastencoderValue = 0;

int val; 

int lastMSB = 0;
int lastLSB = 0;

void setup() {
  lcd.begin(16, 2);
  
  myservo.attach(9);

  pinMode(encoderPin1, INPUT); 
  pinMode(encoderPin2, INPUT);

  digitalWrite(encoderPin1, HIGH);
  digitalWrite(encoderPin2, HIGH);

  attachInterrupt(0, updateEncoder, CHANGE); 
  attachInterrupt(1, updateEncoder, CHANGE);

}

void loop(){ 
  lcd.print(int(encoderValue*3.75));
  lcd.print(" Degrees");
  lcd.noDisplay();
  delay(10);
  lcd.display();
  delay(10);
  lcd.clear();
  val = encoderValue*3.75;
  if(val>15) myservo.write(90-val);
  delay(15);
  if(val<15 and val>-15) myservo.write(90);
  delay(15); 
  if(val<-15) myservo.write(90-val);
  delay(15);

}


void updateEncoder(){
  int MSB = digitalRead(encoderPin1);
  int LSB = digitalRead(encoderPin2);

  int encoded = (MSB << 1) |LSB;
  int sum  = (lastEncoded << 2) | encoded;

  if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderValue ++;
  if(sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderValue --;

  lastEncoded = encoded;
}
