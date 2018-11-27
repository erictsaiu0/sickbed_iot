//#include "sb_motor.h"
//#include "Arduino.h"
//
//sb_motor::sb_motor(void){
//  motor_state = 0;
//  sp = 1000;
//  mstime = 0;
//  }
//  
//
//void sb_motor::motor_initial(int stepPin_in, int dirPin_in, int btn_in){
//    stepPin = stepPin_in; 
//    dirPin = dirPin_in;
//    btn = btn_in;
//    pinMode(stepPin,OUTPUT);
//    pinMode(dirPin,OUTPUT);
//    pinMode(btn,INPUT_PULLUP);
//    //up_signal = up_signal_in;
//    work_done = 1;
//
//}
//
//void sb_motor::motor_setup(uint32_t worktime_in, uint32_t sp_in){
//  worktime = worktime;
//  sp = sp_in;
//}
//
//void sb_motor::motor_reset_single(int stepPin, int dirPin,int btn)
//{
//  mstime = micros();
//  switch (motor_state) {
//      case 0:
//        work_done = 0;
//        digitalWrite(dirPin,HIGH);
//        digitalWrite(stepPin,(micros()%sp>(sp/2))?(1):(0));
//        //motor_state = (oneshot(btn))?(1):(0);
//        break;
//        
//      case 1:
//        if(i<50000)
//        {
//          digitalWrite(dirPin,LOW);
//          digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//          i++;  
//        }
//        else
//        {
//          digitalWrite(dirPin,HIGH);
//          digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//          if(oneshot(btn))
//          {
//            motor_state = 2;
//            i = 0;
//          }
//        }
//        break;
//      case 2:
//        if(i<300)
//        {
//          digitalWrite(dirPin,LOW);
//          digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//          i++;  
//        }
//        else
//        {
//          motor_state = 3;
//        }
//        break;
//       case 3:
//       {
//        reset_done = 1;
//        motor_state = 4;
//        work_done = 1;
//        }
//      default:
//        digitalWrite(stepPin,LOW);
//    }
//  }
//
//void sb_motor::motor_up(int stepPin, int dirPin, char up_signal)
//{
//  mstime = micros();
//  up_trig = (oneshot(up_signal=='U'))?1:up_trig;
//
//  if(up_trig)
//  {
//    if(j<worktime)
//    {
//      digitalWrite(dirPin,LOW);
//      digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//      j++;
//    }
//    else
//    {
//      digitalWrite(stepPin,LOW);
//      j=0;
//      up_trig=0;
//    }
//  }
//  }
//
//void sb_motor::motor_down(int stepPin, int dirPin, char down_signal)
//{
//  mstime = micros();
//  
//  down_trig = (oneshot(down_signal=='D'))?1:down_trig;
//
//  if(down_trig)
//  {
//    if(j<worktime)
//    {
//      digitalWrite(dirPin,HIGH);
//      digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//      j++;
//    }
//    else
//    {
//      digitalWrite(stepPin,LOW);
//      j=0;
//      down_trig=0;
//    }
//  }
//  }
//
//void sb_motor::motor_action(int stepPin, int dirPin, char action_signal)
//{
//  
//  mstime = micros();
//  up_trig = (oneshot(action_signal=='U'))?1:up_trig;
//  down_trig = (oneshot(action_signal=='D'))?1:down_trig;
//  return_trig = (oneshot(action_signal=='O'))?1:return_trig;
//
//  if(up_trig && position_state != 'U')
//  {
//    work_done = 0;
//    if(j<worktime)
//    {
//      digitalWrite(dirPin,LOW);
//      digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//      j++;
//    }
//    else
//    {
//      digitalWrite(stepPin,LOW);
//      j=0;
//      up_trig=0;
//      position_state = 'U';
//      work_done = 1;
//    }
//  }
//  else if(down_trig && position_state != 'D')
//  {
//    work_done = 0;
//    if(j<worktime)
//    {
//      digitalWrite(dirPin,HIGH);
//      digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//      j++;
//    }
//    else
//    {
//      digitalWrite(stepPin,LOW);
//      j=0;
//      down_trig=0;
//      position_state = 'U';
//      work_done = 1;
//    }
//  }
//  else if(return_trig)
//  {
//    work_done = 0;
//    switch(position_state)
//    {
//      case 'U':
//      {
//        if(j<worktime)
//        {
//          digitalWrite(dirPin,HIGH);
//          digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//          j++;
//          }
//          else
//          {
//          digitalWrite(stepPin,LOW);
//          j=0;
//          return_trig=0;
//          position_state = 'O';
//          work_done = 1;
//        }
//      }
//      case 'D':
//      {
//        if(j<worktime)
//        {
//          digitalWrite(dirPin,LOW);
//          digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
//          j++;
//        }
//        else
//        {
//          digitalWrite(stepPin,LOW);
//          j=0;
//          return_trig=0;
//          position_state = 'O';
//          work_done = 1;
//        }
//      }
//      case 'O':
//      {
//          return_trig=0;
//          position_state = 'O';
//          work_done = 1;
//        }
//    }
//  }
//  }
//  
//bool sb_motor::oneshot(int btn)
//{
//  bool oneshot_flag = 0;
//  oneshot_newtime = micros();
//  if(!digitalRead(btn))
//  {
//      oneshot_flag = (oneshot_newtime-oneshot_oldtime>oneshot_interval)?(1):(0);
//  }
//  else
//  {
//    oneshot_oldtime = oneshot_newtime;
//    oneshot_flag = 0;
//  }
//    return oneshot_flag;
//  }
//
//  
//void sb_motor::motor_action_decode(char instr)
//{
//  
//  switch(instr)
//  {
//    case 'L':
//    {
//      action_array[0]='U';
//      action_array[1]='O';
//      action_array[2]='U';
//      action_array[3]='O';
//      action_array[4]='U';
//      action_array[5]='O';
//      }
//    case 'R':
//    {
//      action_array[0]='O';
//      action_array[1]='U';
//      action_array[2]='O';
//      action_array[3]='U';
//      action_array[4]='O';
//      action_array[5]='U';
//      }
//    case 'F':
//    {
//      action_array[0]='U';
//      action_array[1]='U';
//      action_array[2]='O';
//      action_array[3]='O';
//      action_array[4]='D';
//      action_array[5]='D';
//      }
//    case 'O':
//    {
//      action_array[0]='O';
//      action_array[1]='O';
//      action_array[2]='O';
//      action_array[3]='O';
//      action_array[4]='O';
//      action_array[5]='O';
//      }
//    
//    }
//  }
//
#include "sb_motor.h"
#include "Arduino.h"

sb_motor::sb_motor(void){
  }

void sb_motor::motor_initial(int stepPin_in, int dirPin_in, int btn_in){
    stepPin = stepPin_in; 
    dirPin = dirPin_in;
    btn = btn_in;
    pinMode(stepPin,OUTPUT);
    pinMode(dirPin,OUTPUT);
    pinMode(btn,INPUT_PULLUP);
    //up_signal = up_signal_in;

}

void sb_motor::motor_setup(uint32_t worktime_in, int sp_in){
  worktime = worktime_in;
  sp = sp_in;
}

void sb_motor::motor_reset_single(int stepPin, int dirPin,int btn)
{
  mstime = micros();
  
//  Serial.println(motor_state);
  switch (motor_state) {
      case 0:
        digitalWrite(dirPin,HIGH);
        digitalWrite(stepPin,(mstime%sp>(sp/2))?HIGH:LOW);
        motor_state = (oneshot(btn))?(1):(0);
        break;
      case 1:
        if(i<15000)
        {
          digitalWrite(dirPin,LOW);
          digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):LOW);
          i++;  
        }
        else
        {
          digitalWrite(dirPin,HIGH);
          digitalWrite(stepPin,(mstime%sp>(sp/2))?HIGH:LOW);
          if(oneshot(btn))
          {
            motor_state = 2;
            i = 0;
          }
        }
        break;
      case 2:
        if(i<20000)
        {
          digitalWrite(dirPin,LOW);
          digitalWrite(stepPin,(mstime%sp>(sp/2))?HIGH:LOW);
          i++;  
        }
        else
        {
          motor_state = 3;
        }
        break;
       case 3:
       {
        reset_done = 1;
        motor_state = 4;
        position_state = 'O';
        i = 0;
        break;
        }
      default:
//        digitalWrite(stepPin,LOW);
        break;
    }
  }

void sb_motor::motor_up(void)
{
  mstime = micros();
    if(j<worktime)
    {
      work_done = 0;
      digitalWrite(dirPin,LOW);
      digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
      j++;
    }
    else
    {
      digitalWrite(stepPin,LOW);
      j=0;
      up_trig=0;
      position_state = 'U';
      work_done = 1;
    }
  }

void sb_motor::motor_down(void)
{
  mstime = micros();
    if(j<worktime)
    {
      work_done = 0;
      digitalWrite(dirPin,HIGH);
      digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
      j++;
    }
    else
    {
      digitalWrite(stepPin,LOW);
      j=0;
      down_trig=0;
      position_state = 'D';
      work_done = 1;
    }
  }

void sb_motor::motor_action(int stepPin, int dirPin, char action_signal)
{ 
  mstime = micros();
  if(action_signal=='U' && position_state != 'U')
  {
  motor_up();
  }
  else if(action_signal == 'D' && position_state != 'D')
  {
  motor_down();
  }
  else if(action_signal == 'O')
  {
    switch(position_state)
    {
      case 'U':
      {
        if(j<worktime)
        {
          work_done = 0;
          digitalWrite(dirPin,HIGH);
          digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
          j++;
          }
          else
          {
          digitalWrite(stepPin,LOW);
          j=0;
          return_trig=0;
          position_state = 'O';
          work_done = 1;
        }
      }
      case 'D':
      {
        if(j<worktime)
        {
          work_done = 0;
          digitalWrite(dirPin,LOW);
          digitalWrite(stepPin,(mstime%sp>(sp/2))?(1):(0));
          j++;
        }
        else
        {
          digitalWrite(stepPin,LOW);
          j=0;
          return_trig=0;
          position_state = 'O';
          work_done = 1;
        }
      }
      case 'O':
      {
        }
    }
  }
  }
  
bool sb_motor::oneshot(int btn)
{
  bool oneshot_flag = 0;
  oneshot_newtime = micros();
  if(!digitalRead(btn))
  {
      oneshot_flag = (oneshot_newtime-oneshot_oldtime>oneshot_interval)?1:0;
  }
  else
  {
    oneshot_oldtime = oneshot_newtime;
    oneshot_flag = 0;
  }
    return oneshot_flag;
  }

bool sb_motor::oneshot_signal(char sig)
{
  bool oneshot_flag = 0; 
  oneshot_newtime = micros();
  if(sig == 'U' || sig == 'D' || sig == 'O')
  {
    oneshot_flag = (oneshot_newtime-oneshot_oldtime<5)?1:0;
    }
  else
  {
    oneshot_oldtime = oneshot_newtime;
    oneshot_flag = 0;
    }
    return oneshot_flag;
  
  }
