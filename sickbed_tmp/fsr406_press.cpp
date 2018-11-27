#include "fsr406_press.h"
#include "Arduino.h"

fsr406_press::fsr406_press(void)
{
  }

void fsr406_press::fsr406_initial(uint8_t datapin_in, float trigger_value_in)
{
  datapin = datapin_in;
  trigger_value = trigger_value_in;
  }

void fsr406_press::fsr406_read(void)
{
  float data1,data2,data3,data4,data5;
//  analog_mux(datapin);
  delay(200);
  data1 = analogRead(datapin);
  data2 = analogRead(datapin);
  data3 = analogRead(datapin);
  data4 = analogRead(datapin);
  data5 = analogRead(datapin);
  press_data = (data2 + data3 + data4)/3;// * (-1) + 1021;
  }

void fsr406_press::save_array(float data1,float data2,float data3,float data4,float data5,float data6)
{
  data_array[0] = data1;
  data_array[1] = data2;
  data_array[2] = data3;
  data_array[3] = data4;
  data_array[4] = data5;
  data_array[5] = data6;
  }
  
void fsr406_press::print_array(void)
{
  Serial.println("press_data:  ");
  for(int i=0;i<6;i++)
  {
    Serial.println(data_array[i]);
    }
  }

bool fsr406_press::press_trig_solo(float data)
{
  bool trigger;
  trigger = (data<=trigger_value);

  return trigger;
  }

char fsr406_press::press_trig_total(float data_array[])
{
  byte trig_B1, trig_B2, trig_B3, trig_B4, trig_B5, trig_B6;

  trig_B1 = press_trig_solo(data_array[0]);
  trig_B2 = press_trig_solo(data_array[1]);
  trig_B3 = press_trig_solo(data_array[2]);
  trig_B4 = press_trig_solo(data_array[3]);
  trig_B5 = press_trig_solo(data_array[4]);
  trig_B6 = press_trig_solo(data_array[5]);
  
  if(trig_B1+trig_B3+trig_B5>=2 || trig_B2+trig_B4+trig_B6>=2)
  {
    return 'S';
    //patient stay
  }
  else 
  {
    return 'A';
    //patient away
  }
  }

void fsr406_press::print_trig_data(void)
{
  byte trig_B1, trig_B2, trig_B3, trig_B4, trig_B5, trig_B6;

  trig_B1 = press_trig_solo(data_array[0]);
  trig_B2 = press_trig_solo(data_array[1]);
  trig_B3 = press_trig_solo(data_array[2]);
  trig_B4 = press_trig_solo(data_array[3]);
  trig_B5 = press_trig_solo(data_array[4]);
  trig_B6 = press_trig_solo(data_array[5]);

  Serial.println("press trigger data: ");
  Serial.print("B1: ");
  Serial.println(trig_B1);
  Serial.print("B2: ");
  Serial.println(trig_B2);
  Serial.print("B3: ");
  Serial.println(trig_B3);
  Serial.print("B4: ");
  Serial.println(trig_B4);
  Serial.print("B5: ");
  Serial.println(trig_B5);
  Serial.print("B6: ");
  Serial.println(trig_B6);
  }
  
void fsr406_press::wait(int interval)
{
  unsigned long timenow = 0;
  timenow = micros();
  while(micros() < timenow + interval){}
  timenow = 0;
  }

void fsr406_press::analog_mux(int pin)
{
  switch(pin)
  {
    case 54:
    {
      pinMode(54,INPUT_PULLUP);
      pinMode(55,OUTPUT);
      pinMode(56,OUTPUT);
      pinMode(57,OUTPUT);
      pinMode(58,OUTPUT);
      pinMode(59,OUTPUT);
      digitalWrite(55,LOW);
      digitalWrite(56,LOW);
      digitalWrite(57,LOW);
      digitalWrite(58,LOW);
      digitalWrite(59,LOW);
      }  
    case 55:
    {
      pinMode(55,INPUT_PULLUP);
      pinMode(54,OUTPUT);
      pinMode(56,OUTPUT);
      pinMode(57,OUTPUT);
      pinMode(58,OUTPUT);
      pinMode(59,OUTPUT);
      digitalWrite(54,LOW);
      digitalWrite(56,LOW);
      digitalWrite(57,LOW);
      digitalWrite(58,LOW);
      digitalWrite(59,LOW);
    }
    case 56:
    {
      pinMode(56,INPUT_PULLUP);
      pinMode(54,OUTPUT);
      pinMode(55,OUTPUT);
      pinMode(57,OUTPUT);
      pinMode(58,OUTPUT);
      pinMode(59,OUTPUT);
      digitalWrite(54,LOW);
      digitalWrite(55,LOW);
      digitalWrite(57,LOW);
      digitalWrite(58,LOW);
      digitalWrite(59,LOW);
    }
    case 57:
    {
      pinMode(57,INPUT_PULLUP);
      pinMode(54,OUTPUT);
      pinMode(55,OUTPUT);
      pinMode(56,OUTPUT);
      pinMode(58,OUTPUT);
      pinMode(59,OUTPUT);
      digitalWrite(54,LOW);
      digitalWrite(55,LOW);
      digitalWrite(56,LOW);
      digitalWrite(58,LOW);
      digitalWrite(59,LOW);
    }
    case 58:
    {
      pinMode(58,INPUT_PULLUP);
      pinMode(54,OUTPUT);
      pinMode(55,OUTPUT);
      pinMode(56,OUTPUT);
      pinMode(57,OUTPUT);
      pinMode(59,OUTPUT);
      digitalWrite(54,LOW);
      digitalWrite(55,LOW);
      digitalWrite(56,LOW);
      digitalWrite(57,LOW);
      digitalWrite(59,LOW);
    }
    case 59:
    {
      pinMode(59,INPUT_PULLUP);
      pinMode(54,OUTPUT);
      pinMode(55,OUTPUT);
      pinMode(56,OUTPUT);
      pinMode(57,OUTPUT);
      pinMode(58,OUTPUT);
      digitalWrite(54,LOW);
      digitalWrite(55,LOW);
      digitalWrite(56,LOW);
      digitalWrite(57,LOW);
      digitalWrite(58,LOW);
    }
  }
  }
