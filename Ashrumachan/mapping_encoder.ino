#define enc_11 2
#define enc_12 4
#define enc_21 3
#define enc_22 5

volatile int enc1_val = 0
volatile int enc2_val = 0;
int x_counter,x_motion,y_counter,y_motion;
void setup() {
  pinMode(enc_11, INPUT);
  digitalWrite(enc_11, HIGH);
  pinMode(enc_12, INPUT);
  digitalWrite(enc_12, HIGH);

  pinMode(enc_21, INPUT);
  digitalWrite(enc_21, HIGH);
  pinMode(enc_22, INPUT);
  digitalWrite(enc_22, HIGH);

  attachInterrupt(digitalPinToInterrupt(2), func, RISING);
  attachInterrupt(digitalPinToInterrupt(3), func1, RISING);

  Serial.begin(115200);
}

void loop() 
{
  Serial.print(enc1_val);
  Serial.print("   ");
  Serial.print(enc2_val);
  Serial.print("   ");
  x_counter=enc1_val/100;
  if(x_counter>100)
  x_counter=0;
  y_counter=enc2_val/100;
  if(y_counter>100)
  y_counter=0;
  
  x_motion=map(x_counter,-x_counter,x_counter,-255,255);
  y_motion=map(y_counter,-y_counter,y_counter,-255,255);

}


void func() {
  if (digitalRead(enc_12) != digitalRead(enc_11)) {
    enc1_val++ ;
  }

  else {
    enc1_val-- ;
  }

}


void func1() {
  if (digitalRead(enc_22) != digitalRead(enc_21)) {
    enc2_val++ ;
  }

  else {
    enc2_val-- ;
  }

}
