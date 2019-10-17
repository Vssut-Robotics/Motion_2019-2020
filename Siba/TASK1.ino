#define A 18
#define B 4
#define C 19
#define D 5

volatile int ENCx_val = 0;
volatile int ENCy_val = 0;
int counter1, initial_x, counter2, initial_y, final_x, final_y, x_val, y_val, arr[2][2] = {{0, 0}, {50, 50}};
int p = 50;
int arr[4][2] = {{0, 0}, {p / 2 - 2, p / 2 - 2}, {p / 2 - 2, p / 2}, {p, p}};
int d1 = 6, d2 = 7, d3 = 8, d4 = 9;
int d_1, d_2, d_3, d_4;
int s_1 = 23, s_2 = 25, s_3 = 27, s_4 = 29;
int s1, s2, s3, s4;
int sf = 1, w = 0, angle;
void siba();
void prasad();
void setup() {
  pinMode(A, INPUT);
  digitalWrite(A, HIGH);
  pinMode(B, INPUT);
  digitalWrite(B, HIGH);

  pinMode(C, INPUT);
  digitalWrite(C, HIGH);
  pinMode(D, INPUT);
  digitalWrite(D, HIGH);

  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(18), siba, RISING);
  attachInterrupt(digitalPinToInterrupt(19), prasad, RISING);

  Serial.begin(115200);
}

void loop()
{
  counter1 = ENCx_val / 100;
  counter2 = ENCy_val / 100;
  while (counter1 != arr[1][0] && counter2 != arr[1][1])
  {
    x_val = arr[1][0] - counter1;
    y_val = arr[1][1] - counter2;
    angle = atan2(y_val, x_val);
    initial_x = map((90 - angle), -90, 90, -255, 255);
    initialy = map(angle, -90, 90, -255, 255);
    motion(initial_x, iniyial_y);
  }
}


void siba()
{
  if (digitalRead(B) != digitalRead(A)) {
    ENCx_val++ ;
  }

  else
  {
    ENCx_val-- ;
  }

}


void prasad()
{
  if (digitalRead(D) != digitalRead(C) {
  ENCy_val++ ;
}

else {
  ENCy_val-- ;
}

}
void motion(int initial_x, int initial_y)
{
  final_x = initial_x ;
  final_y = initial_y ;

  sf = 1;
  s1 = sf * (0.1768 * finial_x + 0.1768 * finial_y + 0.25 * w);
  s2 = sf * (0.1768 * finial_x + 0.1768 * finial_y + 0.25 * w);
  s3 = sf * (-0.1768 * finial_x - 0.1768 * finial_y+ 0.25 * w);
  s4 = sf * (-0.1768 *finial_x - 0.1768 * finial_y + 0.25 * w);
  d_1 = (s1 > 0 ? 1 : 0);
  d_2 = (s2 > 0 ? 1 : 0);
  d_3 = (s3 > 0 ? 1 : 0);
  d_4 = (s4 > 0 ? 1 : 0);
  digitalWrite(6, d_1);
  digitalWrite(7, d_2);
  digitalWrite(8, d_3);
  digitalWrite(9, d_4);
  analogWrite(23, s1);
  analogWrite(25, s2);
  analogWrite(27, s3);
  analogWrite(29, s4);
}
