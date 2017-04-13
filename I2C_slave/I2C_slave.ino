
#include<Wire.h>
#include<SoftwareSerial.h>
#include<Cytron_PS2Shield.h>
byte a[24];
Cytron_PS2Shield ps2(2,3);
int n,i;
void setup() {
  ps2.begin(9600);
  Serial.begin(9600);
  Wire.begin(5);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);  
  pinMode(A0,INPUT);
  pinMode(9,INPUT);
  pinMode(A2,INPUT);
  }



void loop() {  
  while(1)
  {
      a[0] = ps2.readButton(PS2_SQUARE);
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
      a[18] = 0;
      a[19] = 0;
      a[20] = 0;
      a[21] = 0;
      a[22] = digitalRead(9);
      a[23] = analogRead(A2);

      n=analogRead(A0);
      i=18;
      
      for(;n>0;)
      {
        if(n-255>=0)
            {
              a[i]=255;  
            }
         else a[i]=n;
      i++;
      n=n-255;
      }
      
    for(i=0;i<24;i++)
      {
          Serial.print(a[i]);
          Serial.print("  ");
      }
      Serial.println();
      Wire.onRequest(sendevent);
  }
  } 

void sendevent()
{
       Wire.write(a,24);
}



