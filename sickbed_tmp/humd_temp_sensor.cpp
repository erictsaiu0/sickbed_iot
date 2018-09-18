#include "humd_temp_sensor.h"
#include "Arduino.h"

humd_temp_sensor::humd_temp_sensor(void){
}


void humd_temp_sensor::tca_initial(void){
  tcaselect(0);
  myHnm1.begin();
  Serial.println("1st ready!");

  tcaselect(1);
  myHnm2.begin();
  Serial.println("2nd ready!");

  tcaselect(2);
  myHnm3.begin();
  Serial.println("3rd ready!");

  tcaselect(3);
  myHnm4.begin();
  Serial.println("4th ready!");
  
  tcaselect(4);
  myHnm5.begin();
  Serial.println("5th ready!");

  tcaselect(5);
  myHnm6.begin();
  Serial.println("6th ready!");
  
  tcaselect(6);
  myHnm7.begin();
  Serial.println("7th ready!");
  
  tcaselect(7);
  myHnm8.begin();
  Serial.println("8th ready!");

  tcaselect(8);
  myHnm9.begin();
  Serial.println("9th ready!");
  
  tcaselect(9);
  myHnm10.begin();
  Serial.println("10th ready!");
  
  tcaselect(10);
  myHnm11.begin();
  Serial.println("11th ready!");
  
  tcaselect(11);
  myHnm12.begin();
  Serial.println("12th ready!");

  Serial.println("===============HnM setup ready=================");
}
/*
void humd_temp_sensor::scan(void)
{
  while (!Serial);
    Wire.begin();
    Serial.println("\nTCAScanner ready!");
    
    for (uint8_t t=0; t<16; t++) {
      tcaselect(t);
      Serial.print("TCA Port #"); Serial.println(t);

      for (uint8_t addr = 0; addr<=127; addr++) {
        if (addr == TCAADDR1 or addr == TCAADDR2) continue;
      
        uint8_t data;
        if (! twi_writeTo(addr, &data, 0, 1, 1)) {
           Serial.print("Found I2C 0x");  Serial.println(addr,HEX);
        }
      }
    }
    Serial.println("\ndone");
}*/

void humd_temp_sensor::tcaselect(int i)
{
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

void humd_temp_sensor::data_filter_6(float data1, float data2 ,float data3, float data4, float data5, float data6)
{
    data_array[0] = (data_avail(data1) == 'a') ? data1 : data_array[0];
    data_array[1] = (data_avail(data2) == 'a') ? data2 : data_array[1];
    data_array[2] = (data_avail(data3) == 'a') ? data3 : data_array[2];
    data_array[3] = (data_avail(data4) == 'a') ? data4 : data_array[3];
    data_array[4] = (data_avail(data5) == 'a') ? data5 : data_array[4];
    data_array[5] = (data_avail(data6) == 'a') ? data6 : data_array[5];
    Serial.println("data output: ");
      for(int i=0;i<=5;i++)
      {
        Serial.print(data_array[i]);
        Serial.println(" ");
      }
}

void humd_temp_sensor::data_read(void){

  tcaselect(0);
  hmd1 = myHnm1.readHumidity();
  tmp1 = myHnm1.readTemperature();
  
  tcaselect(1);
  hmd2 = myHnm2.readHumidity();
  tmp2 = myHnm2.readTemperature();

  tcaselect(2);
  hmd3 = myHnm3.readHumidity();
  tmp3 = myHnm3.readTemperature();

  tcaselect(3);
  hmd4 = myHnm4.readHumidity();
  tmp4 = myHnm4.readTemperature();

  tcaselect(4);
  hmd5 = myHnm5.readHumidity();
  tmp5 = myHnm5.readTemperature();

  tcaselect(5);
  hmd6 = myHnm6.readHumidity();
  tmp6 = myHnm5.readTemperature();

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
  hmd12 = myHnm12.readHumidity();
  
  data_filter_6(hmd1,hmd2,hmd3,hmd4,hmd5,hmd6);
  hmd_data_array[6] = data_array[6];
  
  data_filter_6(tmp1,tmp2,tmp3,tmp4,tmp5,tmp6);
  tmp_data_array[6] = data_array[6];
}

byte humd_temp_sensor::hnt_trig_solo(float humd,float temp)
{
  int humid_solo=60;
  int temp_solo=35;
  int humid_inter=50;
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
  if(trig_B1 + trig_B3 + trig_B5>0)
  {
    return 'L';
    //trigger left side flipping
  }
  else if(trig_B2 + trig_B4 + trig_B6>0)
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
