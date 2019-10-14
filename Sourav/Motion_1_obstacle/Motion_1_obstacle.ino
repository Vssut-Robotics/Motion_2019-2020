const unsigned char x_encoder[2] = {,};         //first pin A then pin B
const unsigned char y_encoder[2] = {,};         //first pin A then pin B
const unsigned char motor1[2] = {,};    //first direction pin then pwm pin
const unsigned char motor2[2] = {,};    //first direction pin then pwm pin
const unsigned char motor3[2] = {,};    //first direction pin then pwm pin
const unsigned char motor4[2] = {,};    //first direction pin then pwm pin

const int coordinate_size = ;
const float obstacle[2] = {,};
const float min_distance = ;

volatile int x_val = 0;
volatile int y_val = 0;
float x_coordinate = 0,y_coordinate = 0;
int x=0,y=0,w=0;
int motor_speed[4][2];
float end_point[2] = {,};
int angle;
int sf = 1;

void setup() {
  pinMode(x_encoder[0],INPUT_PULLUP);
  pinMode(y_encoder[0],INPUT_PULLUP);
  pinMode(x_encoder[1],INPUT);
  pinMode(y_encoder[1],INPUT);
  
  pinMode(motor1[0],OUTPUT);
  pinMode(motor2[0],OUTPUT);
  pinMode(motor3[0],OUTPUT);
  pinMode(motor4[0],OUTPUT);
  pinMode(motor1[1],OUTPUT);
  pinMode(motor2[1],OUTPUT);
  pinMode(motor3[1],OUTPUT);
  pinMode(motor4[1],OUTPUT);
  
  attachInterrupt(digitalPinToInterrupt(x_encoder[0]), calc_x, RISING);
  attachInterrupt(digitalPinToInterrupt(y_encoder[0]), calc_y, RISING);
}

void loop() {
  if(x_val >= coordinate_size)
  {
    x_coordinate = (int)x_coordinate + 1;
    x_val = x_val % coordinate_size;
  }
  else if(x_val <= -coordinate_size)
  {
    x_coordinate = (int)x_coordinate - 1;
    x_val = x_val % coordinate_size;
  }
  
  if(y_val >= coordinate_size)
  {
    y_coordinate = (int)y_coordinate + 1;
    y_val = y_val % coordinate_size;
  }
  else if(y_val <= -coordinate_size)
  {
    y_coordinate = (int)y_coordinate - 1;
    y_val = y_val % coordinate_size;
  }
  x_coordinate = x_coordinate + float(x_val/coordinate_size);
  y_coordinate = y_coordinate + float(y_val/coordinate_size);
  
  if(calc_distance(end_point) > 2.0)
  {
    if(calc_dist(onstacle) <= min_distance)
    {
      deviate();
    }
    else
    {
      if(end_point[0] != x_coordinate)
        angle = atan((end_point[1] - y_coordinate) / (end_point[0] - x_coordinate)) * 57;
      else 
        angle = 90;    
      x = map((90 - abs(angle)), 0, 90, 0, 255);
      y = map(abs(angle), 0, 90, 0, 255);
      if(end_point[0] < x_coordinate) x = -1 * x;
      if(end_point[1] < y_coordinate) y = -1 * y;
    }
    motion();
  }
}

void calc_x()
{
  if (digitalRead(x_encoder[0]) == digitalRead(x_encoder[1])) 
    x_val--;
  else
    x_val++;
}

void calc_y()
{
  if (digitalRead(y_encoder[0]) == digitalRead(y_encoder[1])) 
    y_val--;
  else
    y_val++;
}

float calc_dist(int x_co, int y_co)
{
  return (((x_co - x_coordinate) * (x_co - x_coordinate)) + ((y_co - y_coordinate) * (y_co - y_coordinate)));
}

void deviate()
{
  if(obstacle[1] != y_coordinate)
    angle = atan((x_coordinate - obstacle[0]) / (obstacle[1] - y_coordinate)) * 57;
  else
    angle = 90;
  x = map((90 - abs(angle)), 0, 90, 0, 255);
  y = map(abs(angle), 0, 90, 0, 255);
  if((x_coordinate < obstacle[0]) || (x_coordinate == obstacle[0] && end_point[0] < x_coordinate)) x = -1 * x;
  if((y_coordinate > obstacle[1]) || (y_coordinate == obstacle[1] && end_point[1] < y_coordinate)) y = -1 * y;
}

void motion()
{ 
  motor_speed[0][1] = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  motor_apeed[1][1] = sf * (0.1768 * x + 0.1768 * y + 0.25 * w);
  motor_apeed[2][1] = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);
  motor_apeed[3][1] = sf * (-0.1768 * x - 0.1768 * y + 0.25 * w);

  motor_apeed[0][0] = (s_1 > 0 ? 1 : 0);
  motor_apeed[1][0] = (s_2 > 0 ? 1 : 0);
  motor_apeed[2][0] = (s_3 > 0 ? 1 : 0);
  motor_apeed[3][0] = (s_4 > 0 ? 1 : 0);

  digitalWrite(d1, motor_apeed[0][0]);
  digitalWrite(d2, motor_apeed[1][0]);
  digitalWrite(d3, motor_apeed[2][0]);
  digitalWrite(d4, motor_apeed[3][0]);

  analogWrite(s1, abs(motor_apeed[0][1]));
  analogWrite(s2, abs(motor_apeed[1][1]));
  analogWrite(s3, abs(motor_apeed[2][1]));
  analogWrite(s4, abs(motor_apeed[3][1]));
}
