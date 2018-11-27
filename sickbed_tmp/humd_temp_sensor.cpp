#include "humd_temp_sensor.h"
#include "Arduino.h"
#include <Wire.h>
//#include <I2C.h>

humd_temp_sensor::humd_temp_sensor(void){
}


void humd_temp_sensor::tca_initial(int rst_pin_in){
  Wire.begin();

  rst_pin = rst_pin_in;
  
  
  pinMode(rst_pin,INPUT);
  digitalWrite(rst_pin,HIGH);
  
  
  tcaselect(0);
  myHnm1.begin();

  tcaselect(1);
  myHnm2.begin();

  tcaselect(2);
  myHnm3.begin();

  tcaselect(3);
  myHnm4.begin();
  
  tcaselect(4);
  myHnm5.begin();

  tcaselect(5);
  myHnm6.begin();
//  Serial.println("===============HnM setup ready=================");

}

void humd_temp_sensor::tcaselect(int i) {
  if (i > 15) return;
  else if(i<=15 && i>7)
  {
    Wire.beginTransmission(TCAADDR2);
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(TCAADDR1);
    Wire.write(1 << (i-8));
    Wire.endTransmission();
    }
  else
  {
    Wire.beginTransmission(TCAADDR1);
    Wire.write(0);
    Wire.endTransmission();
    Wire.beginTransmission(TCAADDR2);
    Wire.write(1 << i);
    Wire.endTransmission();
    }
//  Serial.print("tca link to");
//  Serial.println(i);
  
}


char humd_temp_sensor::data_avail(float data)
{
  if(data<=100 && data>=0)
  {
    return 'a';
  }
  else
  {
    return 'n';
  }
}

void humd_temp_sensor::hmd_data_filter_6(float data1, float data2 ,float data3, float data4, float data5, float data6)
{
    hmd_data_array_temp[0] = (data_avail(data1) == 'a') ? data1 : hmd_data_array_temp[0];
    hmd_data_array_temp[1] = (data_avail(data2) == 'a') ? data2 : hmd_data_array_temp[1];
    hmd_data_array_temp[2] = (data_avail(data3) == 'a') ? data3 : hmd_data_array_temp[2];
    hmd_data_array_temp[3] = (data_avail(data4) == 'a') ? data4 : hmd_data_array_temp[3];
    hmd_data_array_temp[4] = (data_avail(data5) == 'a') ? data5 : hmd_data_array_temp[4];
    hmd_data_array_temp[5] = (data_avail(data6) == 'a') ? data6 : hmd_data_array_temp[5];
}

void humd_temp_sensor::tmp_data_filter_6(float data1, float data2 ,float data3, float data4, float data5, float data6)
{
    tmp_data_array_temp[0] = (data_avail(data1) == 'a') ? data1 : tmp_data_array_temp[0];
    tmp_data_array_temp[1] = (data_avail(data2) == 'a') ? data2 : tmp_data_array_temp[1];
    tmp_data_array_temp[2] = (data_avail(data3) == 'a') ? data3 : tmp_data_array_temp[2];
    tmp_data_array_temp[3] = (data_avail(data4) == 'a') ? data4 : tmp_data_array_temp[3];
    tmp_data_array_temp[4] = (data_avail(data5) == 'a') ? data5 : tmp_data_array_temp[4];
    tmp_data_array_temp[5] = (data_avail(data6) == 'a') ? data6 : tmp_data_array_temp[5];
}

void humd_temp_sensor::data_read(void){


  tcaselect(0);
//  myHnm1.begin();
//  myHnm1.readSensor();
//  hmd1 = myHnm1.getHumidity();
//  tmp1 = myHnm1.getTemperature_C();
  hmd1 = myHnm1.readHumidity();
  tmp1 = myHnm1.readTemperature();

  tcaselect(1);
//  myHnm2.begin();
//  myHnm2.readSensor();
//  hmd2 = myHnm2.getHumidity();
//  tmp2 = myHnm2.getTemperature_C();
  hmd2 = myHnm2.readHumidity();
  tmp2 = myHnm2.readTemperature();

  tcaselect(2);
//  myHnm3.begin();
//  myHnm3.readSensor();
//  hmd3 = myHnm3.getHumidity();
//  tmp3 = myHnm3.getTemperature_C();
  hmd3 = myHnm3.readHumidity();
  tmp3 = myHnm3.readTemperature();

  tcaselect(3);
//  myHnm4.begin();
//  myHnm4.readSensor();
//  hmd4 = myHnm4.getHumidity();
//  tmp4 = myHnm4.getTemperature_C();
  hmd4 = myHnm4.readHumidity();
  tmp4 = myHnm4.readTemperature();

  tcaselect(4);
//  myHnm5.begin();
//  myHnm5.readSensor();
//  hmd5 = myHnm5.getHumidity();
//  tmp5 = myHnm5.getTemperature_C();
  hmd5 = myHnm5.readHumidity();
  tmp5 = myHnm5.readTemperature();

  tcaselect(5);
//  myHnm6.begin();
//  myHnm6.readSensor();
//  hmd6 = myHnm6.getHumidity();
//  tmp6 = myHnm6.getTemperature_C();
  hmd6 = myHnm6.readHumidity();
  tmp6 = myHnm6.readTemperature();

//  Serial.println(hmd1);
//  Serial.println(hmd2);
//  Serial.println(hmd3);
//  Serial.println(hmd4);
//  Serial.println(hmd5);
//  Serial.println(hmd6);
/*
  tcaselect(6);
  hmd7 = myHnm7.readHumidity();

  tcaselect(7);
  hmd8 = myHnm8.readHumidity();

  tcaselect(8);
  hmd9 = myHnm9.readHumidity();

  tcaselect(9);
  hmd10 = myHnm10.readHumidity();

  tcaselect(10);
  hmd11 = myHnm11.readHumidity();

  tcaselect(11);
  hmd12 = myHnm12.readHumidity();*/
  
  hmd_data_filter_6(hmd1,hmd2,hmd3,hmd4,hmd5,hmd6);
  for(int i=0;i<6;i++)
  {
    hmd_data_array[i] = hmd_data_array_temp[i];
    }
    
  tmp_data_filter_6(tmp1,tmp2,tmp3,tmp4,tmp5,tmp6);
  for(int j=0;j<6;j++)
  {
    tmp_data_array[j] = tmp_data_array_temp[j];
    }
  Serial.println("data saved...");
}

void humd_temp_sensor::print_data_array(void)
{
  Serial.println("humd data: ");
      for(int i=0;i<=5;i++)
      {
        Serial.print(i+1);
        Serial.print(" sensor's humd: ");
        Serial.print(hmd_data_array[i]);
        Serial.println(" ");
      }
      for(int j=0;j<=5;j++)
      {
        Serial.print(j+1);
        Serial.print(" sensor's temp: ");
        Serial.print(tmp_data_array[j]);
        Serial.println(" ");
      }
  }

byte humd_temp_sensor::hnt_trig_solo(float humd,float temp)
{
  int humid_solo=70;
  int temp_solo=35;
  int humid_inter=60;
  int temp_inter=30;

  byte trigger;

  trigger = ((humd <= 150 && humd >= humid_solo) || temp >= temp_solo || (humd>=humid_inter && temp >= temp_inter))?1:0;
  
  return trigger;
}

char humd_temp_sensor::hnt_trig_total(float hmd_data_array[],float tmp_data_array[])
{
  //board(a)'s trigger is trig_B(a)
  //board 1/3/5 is for left side of bed, 2/4/6 is for right side
  byte trig_B1, trig_B2, trig_B3, trig_B4, trig_B5, trig_B6;
  trig_B1 = hnt_trig_solo(hmd_data_array[0],tmp_data_array[0]);
  trig_B2 = hnt_trig_solo(hmd_data_array[1],tmp_data_array[1]);
  trig_B3 = hnt_trig_solo(hmd_data_array[2],tmp_data_array[2]);
  trig_B4 = hnt_trig_solo(hmd_data_array[3],tmp_data_array[3]);
  trig_B5 = hnt_trig_solo(hmd_data_array[4],tmp_data_array[4]);
  trig_B6 = hnt_trig_solo(hmd_data_array[5],tmp_data_array[5]);
  if(trig_B1 + trig_B3 + trig_B5>1)
  {
    return 'L';
    //trigger left side flipping
  }
  else if(trig_B2 + trig_B4 + trig_B6>1)
  {
    return 'R';
    //trigger right side flipping
  }
  else
  {
    return 'O';
    //set bed to original status
  }
}

void humd_temp_sensor::print_trig(void)
{
  byte trig_B1, trig_B2, trig_B3, trig_B4, trig_B5, trig_B6;
  trig_B1 = hnt_trig_solo(hmd_data_array[0],tmp_data_array[0]);
  trig_B2 = hnt_trig_solo(hmd_data_array[1],tmp_data_array[1]);
  trig_B3 = hnt_trig_solo(hmd_data_array[2],tmp_data_array[2]);
  trig_B4 = hnt_trig_solo(hmd_data_array[3],tmp_data_array[3]);
  trig_B5 = hnt_trig_solo(hmd_data_array[4],tmp_data_array[4]);
  trig_B6 = hnt_trig_solo(hmd_data_array[5],tmp_data_array[5]);

  Serial.println("hnt trigger data: ");
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

void humd_temp_sensor::vib_initial(int clockPin_in, int strobePin_in, int vib_dataPin_in)
{
  clockPin = clockPin_in;
  strobePin = strobePin_in;
  vib_dataPin = vib_dataPin_in;
  pinMode(clockPin,OUTPUT);
  pinMode(strobePin,OUTPUT);
  pinMode(vib_dataPin,OUTPUT);
  
  }

void humd_temp_sensor::vib_work(void)
{
  uint16_t pattern1, pattern2,data;
  uint8_t highbyte;
  uint8_t lowbyte;

  pattern1 = 2730;
  pattern2 = 1365;

  for(int i=0;i<500;i++)
  {
//    data = (i%2)?pattern1:pattern2;
    data = 0xFFFF;
    highbyte = (data >> 8) & 0xFF;
    lowbyte = data & 0xFF;

    digitalWrite(strobePin, LOW);
  
    shiftOut(vib_dataPin, clockPin, LSBFIRST, lowbyte);
    shiftOut(vib_dataPin, clockPin, LSBFIRST, highbyte);

    digitalWrite(strobePin, HIGH);
    Serial.println(data);
    }
}

void humd_temp_sensor::tca_reset(void)
{
  digitalWrite(rst_pin,LOW);
  wait(5);
  digitalWrite(rst_pin,HIGH);
  }

void humd_temp_sensor::wait(int interval)
{
  unsigned long timenow = 0;
  timenow = micros();
  while(micros() < timenow + interval){}
  timenow = 0;
  }

