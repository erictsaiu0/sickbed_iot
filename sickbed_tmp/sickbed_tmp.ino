#include "sb_motor.h"
#include "humd_temp_sensor.h"
#include "fsr406_press.h"
#include "us_trig.h"
#include "ESPMaster.h"
#include <SPI.h>

//define mtr pin
#define mtr1_step  2
#define mtr2_step 3
#define mtr3_step 4
#define mtr4_step 5
#define mtr5_step 6
#define mtr6_step 7
#define mtr1_dir  22
#define mtr2_dir  23
#define mtr3_dir  24
#define mtr4_dir  25
#define mtr5_dir  26
#define mtr6_dir  27
#define mtr1_btn  13
#define mtr2_btn  12
#define mtr3_btn  11
#define mtr4_btn  10
#define mtr5_btn  9
#define mtr6_btn  8

//define press sensor pin
#define p1_pin    54
#define p2_pin    55
#define p3_pin    56
#define p4_pin    57
#define p5_pin    58
#define p6_pin    59
//define ultrasonic sensor pin
#define us_trig1  32
#define us_echo1  33
#define us_trig2  34
#define us_echo2  35
#define us_trig3  36
#define us_echo3  37
#define us_trig4  38
#define us_echo4  39
//define on-bed controller pin
#define ctrl_up   42
#define ctrl_re   43
#define ctrl_down 44
//define vibrator pin   
#define vib_dataPin  28
#define vib_stb  29
#define vib_clk  30
//other pin
#define tca_rst 31

//define motor parameters
#define mtr_worktime  20000    //每次收到上下指令轉的時間
#define mtr_step_time 1600    //步階馬達每步的時間
//define press parameters
#define press_trig_value 100
//define ultrasonic sensor parameters
#define us_trig_value 10

//declaration of motor functions
sb_motor mtr1;
sb_motor mtr2;
sb_motor mtr3;
sb_motor mtr4;
sb_motor mtr5;
sb_motor mtr6;
sb_motor mtr_t;
//declaration of hunid and temperature sesnors
humd_temp_sensor hnt;
//declaration of ultrasonic sensors
us_trig ustotal;
//declaration of fsr406 sensors
fsr406_press p1;
fsr406_press p2;
fsr406_press p3;
fsr406_press p4;
fsr406_press p5;
fsr406_press p6;
fsr406_press ptotal;
//declaration of SPI communication
ESPMaster esp(53);

char humd_temp_command,press_status,us_status,system_status;
int mtr_work_state = 0;

void setup(){
  system_initial();

  hnt.vib_initial(vib_clk, vib_stb, vib_dataPin);

  uint32_t newsetuptime,oldsetuptime;
  oldsetuptime = millis();
  newsetuptime = millis();
  while(newsetuptime - oldsetuptime < 500)
  {
    newsetuptime = millis();
    }
    
  send("Hello Slave!");

  system_status = 'R';
}

void loop(){
//  Serial.print("status: ");
//  Serial.println(system_status);
  
  switch(system_status)
  {
    case 'R'://status: sensor reading
    {
      sensor_read();
      Serial.println("read done.");
      system_status = 'C';

//      hnt.vib_work();
      break;
      }
    case 'M'://status: motor working
    {
      mtr_ctrl();
//      Serial.println(".....................motor work..................");
//      system_status = 'C';
      break;
      }
    case 'C'://status: communicating
    {
      send_data();
      system_status = 'R';
      break;
      }
  }

  }

void system_initial(void)
{
  Serial.begin(115200);
  
  mtr1.motor_initial(mtr1_step,mtr1_dir,mtr1_btn);
  mtr2.motor_initial(mtr2_step,mtr2_dir,mtr2_btn);
  mtr3.motor_initial(mtr3_step,mtr3_dir,mtr3_btn);
  mtr4.motor_initial(mtr4_step,mtr4_dir,mtr4_btn);
  mtr5.motor_initial(mtr5_step,mtr5_dir,mtr5_btn);
  mtr6.motor_initial(mtr6_step,mtr6_dir,mtr6_btn);


  mtr1.motor_setup(mtr_worktime,mtr_step_time);
  mtr2.motor_setup(mtr_worktime,mtr_step_time);
  mtr3.motor_setup(mtr_worktime,mtr_step_time);
  mtr4.motor_setup(mtr_worktime,mtr_step_time);
  mtr5.motor_setup(mtr_worktime,mtr_step_time);
  mtr6.motor_setup(mtr_worktime,mtr_step_time);

  hnt.vib_initial(vib_clk, vib_stb, vib_dataPin);  
  hnt.tca_initial(tca_rst);
  
  p1.fsr406_initial(p1_pin,press_trig_value);
  p2.fsr406_initial(p2_pin,press_trig_value);
  p3.fsr406_initial(p3_pin,press_trig_value);
  p4.fsr406_initial(p4_pin,press_trig_value);
  p5.fsr406_initial(p5_pin,press_trig_value);
  p6.fsr406_initial(p6_pin,press_trig_value);

  ustotal.us_trig_initial(us_echo1,us_trig1,us_echo2,us_trig2,us_echo3,us_trig3,us_echo4,us_trig4);
  ustotal.us_trig_setup(us_trig_value);

  SPI.begin();
  esp.begin();
  Serial.println("initial done.");

  system_status = 'M';
  }

void sensor_read()
{
  Serial.println("reading.....");
  hnt.data_read();
  humd_temp_command = hnt.hnt_trig_total(hnt.hmd_data_array,hnt.tmp_data_array);
  hnt.print_data_array();
  hnt.print_trig();
  Serial.println(humd_temp_command);

  ustotal.us_trig_read();
  us_status = ustotal.us_trig_total(ustotal.data_array);
  ustotal.print_array();

  p1.fsr406_read();
  p2.fsr406_read();
  p3.fsr406_read();
  p4.fsr406_read();
  p5.fsr406_read();
  p6.fsr406_read();
  ptotal.save_array(p1.press_data,p2.press_data,p3.press_data,p4.press_data,p5.press_data,p6.press_data);
  press_status = ptotal.press_trig_total(ptotal.data_array);
  
  for(int i=0;i<6;i++)
  {
    Serial.println(ptotal.data_array[i]);
    }
    Serial.println();

//  delay(500);
//  hnt.vib_work();
Serial.println("data set done...");
}

void mtr_ctrl(void)
{
  switch(mtr_work_state)
  {
    case 0:
    {
//      mtr_work_state = 1;
      mtr1.motor_reset_single(mtr1.stepPin,mtr1.dirPin,mtr1.btn);
      mtr2.motor_reset_single(mtr2.stepPin,mtr2.dirPin,mtr2.btn);
      mtr3.motor_reset_single(mtr3.stepPin,mtr3.dirPin,mtr3.btn);
      mtr4.motor_reset_single(mtr4.stepPin,mtr4.dirPin,mtr4.btn);
      mtr5.motor_reset_single(mtr5.stepPin,mtr5.dirPin,mtr5.btn);
      mtr6.motor_reset_single(mtr6.stepPin,mtr6.dirPin,mtr6.btn);
      mtr_work_state = (mtr1.reset_done && mtr2.reset_done && mtr3.reset_done && mtr4.reset_done && mtr5.reset_done && mtr6.reset_done)?1:0;
      break;
    }
    case 1:
    {
      motor_action_decode(humd_temp_command);
      mtr1.motor_action(mtr1.stepPin,mtr1.dirPin,mtr1.action_signal);
      mtr2.motor_action(mtr2.stepPin,mtr2.dirPin,mtr2.action_signal);
      mtr3.motor_action(mtr3.stepPin,mtr3.dirPin,mtr3.action_signal);
      mtr4.motor_action(mtr4.stepPin,mtr4.dirPin,mtr4.action_signal);
      mtr5.motor_action(mtr5.stepPin,mtr5.dirPin,mtr5.action_signal);
      mtr6.motor_action(mtr6.stepPin,mtr6.dirPin,mtr6.action_signal);
      if((humd_temp_command != 'O') && (mtr1.work_done && mtr2.work_done && mtr3.work_done && mtr4.work_done && mtr5.work_done && mtr6.work_done))
      {
        hnt.vib_work();
        }
      mtr_work_state = (mtr1.work_done && mtr2.work_done && mtr3.work_done && mtr4.work_done && mtr5.work_done && mtr6.work_done)?2:mtr_work_state;
      break;
  }
     case 2:
     {
        system_status = 'C';
        mtr_work_state = 1;
        break;
     }
  }
}

void send_data(void)
{
    Serial.println("Start sending...");
    send("data sending");

    send("Board 1 data:");

    send_float_by_char(hnt.hmd_data_array[0]);
    send_float_by_char(hnt.tmp_data_array[0]+500);
    send_float_by_char(ptotal.data_array[0]+10000);

    send("Board 2 data:");

    send_float_by_char(hnt.hmd_data_array[1]);
    send_float_by_char(hnt.tmp_data_array[1]+500);
    send_float_by_char(ptotal.data_array[1]+10000);

    send("Board 3 data:");
 
    send_float_by_char(hnt.hmd_data_array[2]);
    send_float_by_char(hnt.tmp_data_array[2]+500);
    send_float_by_char(ptotal.data_array[2]+10000);

    send("Board 4 data:");
 
    send_float_by_char(hnt.hmd_data_array[3]);
    send_float_by_char(hnt.tmp_data_array[3]+500);
    send_float_by_char(ptotal.data_array[3]+10000);

    send("Board 5 data:");

    send_float_by_char(hnt.hmd_data_array[4]);
    send_float_by_char(hnt.tmp_data_array[4]+500);
    send_float_by_char(ptotal.data_array[4]+10000);

    send("Board 6 data:");

    send_float_by_char(hnt.hmd_data_array[5]);
    send_float_by_char(hnt.tmp_data_array[5]+500);
    send_float_by_char(ptotal.data_array[5]+10000);

    send("ultra 1 data:");
    send_float_by_char(ustotal.data_array[0]);

    send("ultra 2 data:");
    send_float_by_char(ustotal.data_array[1]);

    send("ultra 3 data:");
    send_float_by_char(ustotal.data_array[2]);

    send("ultra 4 data:");
    send_float_by_char(ustotal.data_array[3]);

    send("end sending");
    Serial.println("send end");
    system_status = 'R';

  }

void send(const char * message) {
  Serial.print("Master: ");
  Serial.println(message);
  esp.writeData(message);
  uint32_t newsendtime,oldsendtime;
  oldsendtime = millis();
  newsendtime = millis();
  while(newsendtime - oldsendtime < 10)
  {
    newsendtime = millis();
    }
    
  Serial.print("Slave: ");
  Serial.println(esp.readData());
  Serial.println();
}

void send_float_by_char(float num)
{
  char buff[32]="";
  dtostrf(num,5,3,buff);
  send(buff);
  }

void motor_action_decode(char instr)
{
  
  switch(instr)
  {
    case 'L':
    {
      mtr1.action_signal='U';
      mtr2.action_signal='O';
      mtr3.action_signal='U';
      mtr4.action_signal='O';
      mtr5.action_signal='U';
      mtr6.action_signal='O';
      }
    case 'R':
    {
      mtr1.action_signal='O';
      mtr2.action_signal='U';
      mtr3.action_signal='O';
      mtr4.action_signal='U';
      mtr5.action_signal='O';
      mtr6.action_signal='U';
      }
    case 'F':
    {
      mtr1.action_signal='U';
      mtr2.action_signal='U';
      mtr3.action_signal='O';
      mtr4.action_signal='O';
      mtr5.action_signal='D';
      mtr6.action_signal='D';
      }
    case 'O':
    {
      mtr1.action_signal='O';
      mtr2.action_signal='O';
      mtr3.action_signal='O';
      mtr4.action_signal='O';
      mtr5.action_signal='O';
      mtr6.action_signal='O';
      }
    }
  }
