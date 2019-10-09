//programme for holonomic bot follow shortest path with avoiding some point
//Pulse per rotation
#define ENC_COUNT_REV 100

//let us assume that lenth of bot=100cm 
//xcoordinate(encX) is increase by 2 unit for 100cm changes in x direction 
//ycoordinate(encY) is increase by 2 unit for 100cm changes in y direction 
volatile int encX,encY;

int x,y,w;

void func_want(int d_x,int d_y);

//final coordinate
int p=20;    //(20,20)

//if you remove all coordinates except 1st and last then it will take u to one pos to other in shortest path
int arr[4][2]={{0,0},{p/2-2,p/2-2},{p/2-2,p/2},{p,p}};

int s1=23,s2=25,s3=27,s4=29;
int s_1,s_2,s_3,s_4;
int d_1,d_2,d_3,d_4;
int d1=2,d2=3,d3=4,d4=5;

// Pulse count from both X and Y axis Encoder 
volatile long encoderValueX = 0;
volatile long encoderValueY = 0;
volatile int d_x;
volatile int d_y;

void setup()
{
  // Setup Serial Monitor
  Serial.begin(9600); 
  
  // Set encoder as input with internal pullup  
  pinMode(18, INPUT_PULLUP); 
  pinMode(19, INPUT_PULLUP); 

  pinMode(4,INPUT);
  pinMode(5,INPUT);
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(s3,OUTPUT);
  pinMode(s4,OUTPUT);
  
  // Attach interrupt 
  attachInterrupt(digitalPinToInterrupt(18), updateEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(19), updateEncoder, RISING);
}
 
void loop()
{
  for(int i=1;i<4;i++)
 {
    int d_x=arr[i][1]-arr[i-1][1];
    int d_y=arr[i][2]-arr[i-1][2];
    int angle=atan2(d_y,d_x);
    d_x=map((90-angle),-90,90,-255,255);
    d_y=map(angle,-90,90,255,-255);
 }
   func_want(d_x,d_y);
}
 
void updateEncoder()
{
  //18,19,20,21 are encoder pin 
  if(digitalRead(18)==digitalRead(20))
  encoderValueX--;
  else
  encoderValueX++;
  if(digitalRead(19)==digitalRead(21))
  encoderValueY--;
  else
  encoderValueY++;
   if(encoderValueX/ENC_COUNT_REV>=100)
   {
     encX++;
     encoderValueX=0;
   }
  if(encoderValueX/ENC_COUNT_REV<=-100)
  {
    encX--;
    encoderValueX=0;
  }
  if(encoderValueY/ENC_COUNT_REV>=100)
  {
    encY++;
    encoderValueY=0;
  }
  if(encoderValueY/ENC_COUNT_REV<=-100)
  {
    encY--;
    encoderValueY=0;
  }
}
void func_want(int x,int y)
{
   int sf=1;
  s_1 = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  s_2 = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  s_3 = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);
  s_4 = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);
  d_1=(s_1>0?1:0);
  d_2=(s_2>0?1:0);
  d_3=(s_3>0?1:0);
  d_4=(s_4>0?1:0);
  digitalWrite(d1,d_1);
  digitalWrite(d2,d_2);
  digitalWrite(d3,d_3);
  digitalWrite(d4,d_4);
  analogWrite(s1,s_1);
  analogWrite(s2,s_2);
  analogWrite(s3,s_3);
  analogWrite(s4,s_4);
}
