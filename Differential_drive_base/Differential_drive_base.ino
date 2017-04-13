#include  <Wire.h>

#define m1in  22
#define m2in  23
#define m3in 25 
#define m4in  27
#define pwm1  7
#define pwm2  6
#define pwm3  8
#define pwm4  9
#define deadz  15

int m1 = 0;
int m2 = 0;
int m3 = 0;
int m4 = 0;

byte a[18];
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  for ( int i = 4; i < 13; i++)
  {
    pinMode(i, OUTPUT);
  }
}

void loop()
{
  // put your main code here, to run repeatedly:
  Wire.requestFrom(5, 18);
  for (int i = 0; i < 18; i++)
  {
    a[i] = Wire.read();

  }

  Drive_Base(a[16], a[15], a[14]);
}

int Drive_Base(int a, int b, int c)
{
  int x = a - 123; // map to -128 to 128
  int y = b - 132;
  int rot = c - 123;

  m1 =  x - y + rot ;
  m2 =  -x - y - rot ;
  m3 =  x - y - rot;
  m4 =  -x - y + rot;

  if (m1 > 10)
  {
    digitalWrite(m1in, HIGH);

  }
  else if (m1 < -10)
  {
    digitalWrite(m1in, LOW);
  }

  if (m2 > 10)
  {
    digitalWrite(m2in, HIGH);

  }
  else if (m2 < -10)
  {
    digitalWrite(m2in, LOW);
  }

  if (m3 > 10)
  {
    digitalWrite(m3in, HIGH);

  }
  else if (m3 < -10)
  {
    digitalWrite(m3in, LOW);
  }

  if (m4 > 10)
  {
    digitalWrite(m4in, HIGH);

  }
  else if (m4 < -10)
  {
    digitalWrite(m4in, LOW);
  }


  m1 = abs(m1);
  m2 = abs(m2);
  m3 = abs(m3);
  m4 = abs(m4);




  if ((m1 > -deadz) && (m1 < deadz)) // application of deadzone
    m1 = 0;
  if ((m2 > -deadz) && (m2 < deadz))
    m2 = 0;
  if ((m3 > -deadz) && (m3 < deadz))
    m3 = 0;
  if ((m4 > -deadz) && (m4 < deadz))
    m4 = 0;
  if (m1 > 207) // If speed more than 255 then make it 255 as 255 max for Herkules
    m1 = 255;
  if (m3 > 207)
    m3 = 255;
  if (m1 < 5)
    m1 = 0;
  if (m3 < 5)
    m3 = 0;
  if (m2 < 5)
    m2 = 0;
  if (m2 > 207)
    m2 = 255;
  if (m4 < 5)
    m4 = 0;
  if (m4 > 207)
    m4 = 255;



  /*  Serial.print(m1);
    Serial.print(" ");
    Serial.print(m2);
    Serial.print(" ");
    Serial.print(m3);
    Serial.print(" ");
    Serial.println(m4); */

  analogWrite(pwm1, abs(m1));
  analogWrite(pwm2, abs(m2));
  analogWrite(pwm3, abs(m3));
  analogWrite(pwm4, abs(m4));

}
/*
 *
 * a[0] = ps2.readButton(PS2_SQUARE);
      a[1] = ps2.readButton(PS2_CIRCLE);
      a[2] = ps2.readButton(PS2_TRIANGLE);
      a[3] = ps2.readButton(PS2_CROSS);
      a[4] = ps2.readButton(PS2_LEFT_1);
      a[5] = ps2.readButton(PS2_RIGHT_1);
      a[6] = ps2.readButton(PS2_LEFT_2);
      a[7] = ps2.readButton(PS2_RIGHT_2);
      a[8] = ps2.readButton(PS2_UP);
      a[9] = ps2.readButton(PS2_DOWN);
      a[10] = ps2.readButton(PS2_LEFT);
      a[11] = ps2.readButton(PS2_RIGHT);
      a[12] = ps2.readButton(PS2_SELECT);
      a[13] = ps2.readButton(PS2_START);
      a[14] = ps2.readButton(PS2_JOYSTICK_LEFT_X_AXIS);
      a[15] = ps2.readButton(PS2_JOYSTICK_LEFT_Y_AXIS);
      a[16] = ps2.readButton(PS2_JOYSTICK_RIGHT_X_AXIS);
      a[17] = ps2.readButton(PS2_JOYSTICK_RIGHT_Y_AXIS);

 */
