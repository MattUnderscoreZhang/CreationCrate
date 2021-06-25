# 1 "/Users/matt/Dropbox/Projects/Arduino/Mood_Light/Mood_Light.ino"
int pulse_speed = 1; // how fast the lamp runs
int power = 255; // brightness of the lamp
int photoresistor_pin = 0;
int red_led_pin = 11;
int green_led_pin = 10;
int blue_led_pin = 9;
int darkness; // reading from 0-1024
float RGB[3];
float radian_deg_conversion_const = 180/3.1415926535897932384626433832795;

void setup() {
  // put your setup code here, to run once:
  pinMode(red_led_pin, 0x1);
  pinMode(blue_led_pin, 0x1);
  pinMode(green_led_pin, 0x1);
  digitalWrite(red_led_pin, 0x0);
  digitalWrite(blue_led_pin, 0x0);
  digitalWrite(green_led_pin, 0x0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(float x=0; x<3.1415926535897932384626433832795; x=x+0.00001) {
    RGB[0] = power * ((sin(x * radian_deg_conversion_const))>0?(sin(x * radian_deg_conversion_const)):-(sin(x * radian_deg_conversion_const)));
    RGB[1] = power * ((sin((x + 3.1415926535897932384626433832795/3) * radian_deg_conversion_const))>0?(sin((x + 3.1415926535897932384626433832795/3) * radian_deg_conversion_const)):-(sin((x + 3.1415926535897932384626433832795/3) * radian_deg_conversion_const)));
    RGB[2] = power * ((sin((x + 2*3.1415926535897932384626433832795/3) * radian_deg_conversion_const))>0?(sin((x + 2*3.1415926535897932384626433832795/3) * radian_deg_conversion_const)):-(sin((x + 2*3.1415926535897932384626433832795/3) * radian_deg_conversion_const)));
    darkness = analogRead(photoresistor_pin);
    if(darkness > 900) {
      analogWrite(red_led_pin, RGB[0]);
      analogWrite(blue_led_pin, RGB[1]);
      analogWrite(green_led_pin, RGB[2]);
    }
    else {
      digitalWrite(red_led_pin, 0x0);
      digitalWrite(blue_led_pin, 0x0);
      digitalWrite(green_led_pin, 0x0);
    }
    for(int i=0; i<3; i++) {
      if(RGB[i]<1) delay(20*pulse_speed);
      else if(RGB[i]<5) delay(10*pulse_speed);
      else if(RGB[i]<10) delay(2*pulse_speed);
      else if(RGB[i]<100) delay(pulse_speed);
    }
    delay(1);
  }
}
