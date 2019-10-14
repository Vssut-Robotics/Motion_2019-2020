#include<pinmode.h> //club's library for easy pinmode setup //
#include<math.h> // math header //

#define right 1
#define left 2
#define on 0
#define count_per_unit 100
#define sf 30 // scale factor (subject to change through hit and trial) //
#define r 1 //  radius of imaginary forbidden circle around the obstacle (subject to change through hit and trial)

//-------------------------------------------------------------------library inclusion & macro end here-------------------------------------------------------------------------------//
// variables to store speed //
double s1, s2, s3, s4;
//direction and motor pins//
const int d1 = 23, d2 = 25, d3 = 27, d4 = 29;
const int m1 = 2, m2 = 3, m3 = 4, m4 = 5;
bool dir1, dir2, dir3 , dir4;

// encoder pins //
const int encYpinA = 21;
const int encYpinB = A14;
const int encXpinA = 20;
const int encXpinB = A11;
volatile long x_count = 0, y_count = 0;   // counters for x and y encoder ticks //

//traverse coordinates//
volatile float init_x = 0, init_y = 0;
float dest_x = , dest_y = ; // to be filled as destination coordinates//
float obstacle_x = , obstacle_y = ; // to be filled as obstacle coordinates//

//--------------------------------------------------------------------global variable declaration end here----------------------------------------------------------------------------//

float calc_slope(float x1, float y1, float x2, float y2) {
  return ((y2 - y1) / (x2 - x1));
}

void path() {
  float d = sqrt((pow((obstacle_y - init_y), 2) + (pow((obstacle_x - init_x), 2)))); // distance from obstacle and current position //
  while (init_x <= dest_x && init_y <= dest_y) {  //loop till destination is not reached//
    if (d > r)     // check if distance is greater than the radius of imaginary circle //
label: motion(sf * (dest_x - init_x), calc_slope(init_x, init_y, dest_x, dest_y)*sf * (dest_y - init_y));
    else {
      motion(sf * (intermediate_point() - init_x), calc_slope(init_x, init_y, obstacle_y, intermediate_point())*sf * (obstacle_y - init_y));
      goto label;
    }
  }
}
//---------------------------------------------------------------------end of function------------------------------------------------------------------------------------------------//

// function to check whether the obstacle is on the left side, right side or on the line joining the initial & final coordinates //
int check_point_pos() {
  if (obstacle_y - calc_slope(init_x, init_y, dest_x, dest_y) * obstacle_x > 0)
    return left;
  else if (obstacle_y - calc_slope(init_x, init_y, dest_x, dest_y) * obstacle_x < 0)
    return right;
  else
    return on;
}

//---------------------------------------------------------------------end of function------------------------------------------------------------------------------------------------//

// function to calculate the intermediate point i.e. the nearest x coordinate ( corresponding to y coordinate of obstacle ) from the current coordinate //
float intermediate_point() {
  float x1 = obstacle_x + sqrt(r);
  float x2 = obstacle_x - sqrt(r);
  if (check_point_pos() == left || check_point_pos() == on)
    return x1;
  else if (check_point_pos() == right)
    return x2;
}

//---------------------------------------------------------------------end of function------------------------------------------------------------------------------------------------//


// holonomic drive implementation //
void motion(float x, float y) {
  // holonomic matrix for speed calculation //
  s1 =  (-0.35 * x + 0.35 * y + 0.25 * 0);
  s2 =  (-0.35 * x + -0.35 * y + 0.25 * 0);
  s3 =  (0.35 * x + -0.35 * y + 0.25 * 0);
  s4 =   (0.35 * x + 0.35 * y + 0.25 * 0);

  dir1 = s1 >= 0 ? 0 : 1;
  dir2 = s2 >= 0 ? 0 : 1;
  dir3 = s3 >= 0 ? 0 : 1;
  dir4 = s4 >= 0 ? 0 : 1;

  digitalWrite(d1, dir1);
  digitalWrite(d2, dir2);
  digitalWrite(d3, dir3);
  digitalWrite(d4, dir4);

  analogWrite(m1, abs(s1));
  analogWrite(m2, abs(s2));
  analogWrite(m3, abs(s3));
  analogWrite(m4, abs(s4));
}

//---------------------------------------------------------------------end of function------------------------------------------------------------------------------------------------//

void setup() {
  Serial.begin(115200); //set baud rate//
  IN(4, encYpinA, encYpinB, encXpinA, encXpinB); //input pins//
  OUT(8, d1, d2, d3, d4, m1, m2, m3, m4); //output pins//
  attachInterrupt(digitalPinToInterrupt(encXpinA), Count_X, RISING);
  attachInterrupt(digitalPinToInterrupt(encYpinA), Count_Y, RISING);
  Serial.println("Setup executed");
}

void loop() {
  path ();
}

// ISR for encoder along x axis //
void Count_X ()
{
  int A1state = digitalRead(encXpinA);
  int B1state = digitalRead(encXpinB);
  if (B1state == A1state)
    x_count--;
  else
    x_count++;
  // initial x coordinates updation //
  if (x_count == count_per_unit) {
    ++init_x;
    x_count = 0;
  }
  if (x_count == -count_per_unit) {
    --init_x;
    x_count = 0;
  }
}

// ISR for encoder along y axis //
void Count_Y () {
  int A2state = digitalRead(encYpinA);
  int B2state = digitalRead(encYpinB);
  if (B2state == A2state)
    y_count--;
  else
    y_count++;
  // initial y coordinates updation //
  if (y_count == count_per_unit) {
    ++init_y;
    y_count = 0;
  }
  if (y_count == -count_per_unit) {
    --init_y;
    y_count = 0;
  }
}
