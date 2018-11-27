#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include "webpage.h"

#include "SPISlave.h"
#include "stdlib.h"


const char* ssid = "D-Link_ET";
const char* password = "307307307";

//const char* ssid = "E.T's iPhone";
//const char* password = "77777777";

//const char* ssid = "EricTsai's MacBook Pro";
//const char* password = "";

//const char* ssid = "ranger";
//const char* password = "ranger990"; 
ESP8266WebServer server(80);   //instantiate server at port 80 (http port)

String page = "";
String text_h1 = "";
String text_h2 = "";
String text_h3 = "";
String text_h4 = "";
String text_h5 = "";
String text_h6 = "";
String text_h7 = "";
String text_h8 = "";
String text_h9 = "";
String text_h10 = "";
String text_h11 = "";
String text_h12 = "";

String text_t1 = "";
String text_t2 = "";
String text_t3 = "";
String text_t4 = "";
String text_t5 = "";
String text_t6 = "";
String text_t7 = "";
String text_t8 = "";
String text_t9 = "";
String text_t10 = "";
String text_t11 = "";
String text_t12 = "";

String text_p1 = "";
String text_p2 = "";
String text_p3 = "";
String text_p4 = "";
String text_p5 = "";
String text_p6 = "";

String text_d1 = "";
String text_d2 = "";
String text_d3 = "";
String text_d4 = "";
String text_warn = "";

double humd1,humd2,humd3,humd4,humd5,humd6;
double temp1,temp2,temp3,temp4,temp5,temp6;
float pres1,pres2,pres3,pres4,pres5,pres6;
float dist1,dist2,dist3,dist4;
String warning ;

float Board_data[6][3];
float ultra_data[4];
uint16_t read_status = 0;

void setup(void){  
  digitalWrite(15,LOW);
  digitalWrite(0,LOW);
  digitalWrite(2,HIGH);

 Serial.begin(115200);
// WiFi.mode(WIFI_STA);
 WiFi.begin(ssid, password); //begin WiFi connection
 Serial.println("");
 
 // Wait for connection
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
}
 
 Serial.println("");
 Serial.print("Connected to ");
 Serial.println(ssid);
 Serial.print("IP address: ");
 Serial.println(WiFi.localIP());
 sensor2web_initial();
 server.on("/", handleRoot);
 
 server.begin();
 Serial.println("Web server started!");

//////////////////SPI communication////////////////////////
Serial.setDebugOutput(true);
Serial.println("nodemcu start!");
  char read_type;
  
  // data has been received from the master. Beware that len is always 32
  // and the buffer is autofilled with zeroes if data is less than 32 bytes long
  // It's up to the user to implement protocol for handling data length
  SPISlave.onData([](uint8_t * data, size_t len) {
    String message = String((char *)data);
    (void) len;
    float read_data;

    if (message.equals("Hello Slave!")) {
      SPISlave.setData("Hello Master!");
    } else if (message.equals("Are you alive?")) {
      char answer[33];
      sprintf(answer, "Alive for %lu seconds!", millis() / 1000);
      SPISlave.setData(answer);
    } else {

  if(message.equals("data sending"))
    {
      read_status = 0;
    }
    else if(message.equals("Board 1 data:"))
    {
      read_status = 1;
    }
    else if(message.equals("Board 2 data:"))
    {
      read_status = 2;
    }
    else if(message.equals("Board 3 data:"))
    {
      read_status = 3;
    }
    else if(message.equals("Board 4 data:"))
    {
      read_status = 4;
    }
    else if(message.equals("Board 5 data:"))
    {
      read_status = 5;
    }
    else if(message.equals("Board 6 data:"))
    {
      read_status = 6;
    }
    else if(message.equals("ultra 1 data:"))
    {
      read_status = 7;
    }
    else if(message.equals("ultra 2 data:"))
    {
      read_status = 8;
    }
    else if(message.equals("ultra 3 data:"))
    {
      read_status = 9;
    }
    else if(message.equals("ultra 4 data:"))
    {
      read_status = 10;
    }
    else if(message.equals("end sending"))
    {
      read_status = 87;
      for(int a=0;a<6;a++)
            {
              for(int b=0;b<3;b++)
              {
                Serial.println(Board_data[a][b]);
                }
              }
    }
    else
    {
      switch (read_status)
        {
        case 1:
        {
          read_data = strtof(message.c_str(), 0);
          data_mux(0,read_data);
        }
        case 2:
        {
          read_data = strtof(message.c_str(), 0);
          data_mux(1,read_data);
        }
        case 3:
        {
          read_data = strtof(message.c_str(), 0);
          data_mux(2,read_data);
        }
        case 4:
        {
          read_data = strtof(message.c_str(), 0);
          data_mux(3,read_data);
        }
        case 5:
        {
          read_data = strtof(message.c_str(), 0);
          data_mux(4,read_data);
        }
        case 6:
        {
          read_data = strtof(message.c_str(), 0);
          data_mux(5,read_data);
        }
        case 7:
        {
          read_data = strtof(message.c_str(), 0);
          ultra_data[0] = read_data;
        }
        case 8:
        {
          read_data = strtof(message.c_str(), 0);
          ultra_data[1] = read_data;
        }
        case 9:
        {
          read_data = strtof(message.c_str(), 0);
          ultra_data[2] = read_data;
        }
        case 10:
        {
          read_data = strtof(message.c_str(), 0);
          ultra_data[3] = read_data;
        }
        case 87:
        {
          }
    }
}
      
      SPISlave.setData("Say what?");
      
    }
//    store_data();


    Serial.printf("Master said: %s\n", (char *)data);
  });

  // The master has read out outgoing data buffer
  // that buffer can be set with SPISlave.setData
  SPISlave.onDataSent([]() {
    Serial.println("Answer Sent");
  });

  // status has been received from the master.
  // The status register is a special register that bot the slave and the master can write to and read from.
  // Can be used to exchange small data or status information
  SPISlave.onStatus([](uint32_t data) {
    Serial.printf("Status: %u\n", data);
    SPISlave.setStatus(millis()); //set next status
  });

  // The master has read the status register
  SPISlave.onStatusSent([]() {
    Serial.println("Status Sent");
  });

  // Setup SPI Slave registers and pins
  SPISlave.begin();

  // Set the status register (if the master reads it, it will read this value)
  SPISlave.setStatus(millis());

  // Sets the data registers. Limited to 32 bytes at a time.
  // SPISlave.setData(uint8_t * data, size_t len); is also available with the same limitation
  SPISlave.setData("Ask me a question!");

}
 
void loop(void){
  
 server.handleClient();
 
  humd1 = Board_data[0][0];
  humd2 = Board_data[1][0];
  humd3 = Board_data[2][0];
  humd4 = Board_data[3][0];
  humd5 = Board_data[4][0];
  humd6 = Board_data[5][0];

  temp1 = Board_data[0][1];
  temp2 = Board_data[1][1];
  temp3 = Board_data[2][1];
  temp4 = Board_data[3][1];
  temp5 = Board_data[4][1];
  temp6 = Board_data[5][1];
  
  pres1 = Board_data[0][2];
  pres2 = Board_data[1][2];
  pres3 = Board_data[2][2];
  pres4 = Board_data[3][2];
  pres5 = Board_data[4][2];
  pres6 = Board_data[5][2];

  dist1 = ultra_data[0];
  dist2 = ultra_data[1];
  dist3 = ultra_data[2];
  dist4 = ultra_data[3];

  
  if(Board_data[0][2]>=150 || Board_data[1][2]>=150 || Board_data[2][2]>=150 || Board_data[3][2]>=150 || Board_data[4][2]>=150 || Board_data[5][2]>=150 )
  {
    warning += "Patient not on bed!" ;
    warning += '\n';
  }
  if ((ultra_data[0]<10 && ultra_data[1]<10) || (ultra_data[3]<10 && ultra_data[4]<10))
  {
    warning += "Fence down!";
    warning += '\n';
  }
  if(Board_data[0][0]>=70 || Board_data[1][0]>=70 || Board_data[2][0]>=70 || Board_data[3][0]>=70 || Board_data[4][0]>=70 || Board_data[5][0]>=70 )
  {
    warning += "Patient body too wet!";
    warning += '\n';
  }
  if(Board_data[0][1]>=35 || Board_data[1][1]>=35 || Board_data[2][1]>=35|| Board_data[3][1]>=35 || Board_data[4][1]>=35 || Board_data[5][1]>=35 )
  {
    warning = "Patient body hot!";
    warning += '\n';
  }
  
}


void handleRoot(){
  String s = webpage;
  server.send(200, "text/html", s);
  }

void sensor2web_initial(void)
{
  ////////send humidity data////////
  server.on("/humd1.txt", [](){
   text_h1 = (String)humd1;
   server.send(200, "text_h1/html", text_h1);
 });
 server.on("/humd2.txt", [](){
   text_h2 = (String)humd2;
   server.send(200, "text_h2/html", text_h2);
 });
  server.on("/humd3.txt", [](){
   text_h3 = (String)humd3;
   server.send(200, "text_h3/html", text_h3);
 });
  server.on("/humd4.txt", [](){
   text_h4 = (String)humd4;
   server.send(200, "text_h4/html", text_h4);
 });
  server.on("/humd5.txt", [](){
   text_h5 = (String)humd5;
   server.send(200, "text_h5/html", text_h5);
 });
   server.on("/humd6.txt", [](){
    text_h6 = (String)humd6;
    server.send(200, "text_h6/html", text_h6);
  });
////////send temperature data////////
 server.on("/temp1.txt", [](){
   text_t1 = (String)temp1;
   server.send(200, "text_t1/html", text_t1);
 });
 server.on("/temp2.txt", [](){
   text_t2 = (String)temp2;
   server.send(200, "text_t2/html", text_t2);
 });
  server.on("/temp3.txt", [](){
   text_t3 = (String)temp3;
   server.send(200, "text_t3/html", text_t3);
 });
  server.on("/temp4.txt", [](){
   text_t4 = (String)temp4;
   server.send(200, "text_t4/html", text_t4);
 });
  server.on("/temp5.txt", [](){
   text_t5 = (String)temp5;
   server.send(200, "text_t5/html", text_t5);
 });
   server.on("/temp6.txt", [](){
    text_t6 = (String)temp6;
    server.send(200, "text_t6/html", text_t6);
  });
 ////////send pressure data////////
 server.on("/pres1.txt", [](){
   text_p1 = (String)pres1;
   server.send(200, "text_p1/html", text_p1);
 });
 server.on("/pres2.txt", [](){
   text_p2 = (String)pres2;
   server.send(200, "text_p2/html", text_p2);
 });
  server.on("/pres3.txt", [](){
   text_p3 = (String)pres3;
   server.send(200, "text_p3/html", text_p3);
 });
  server.on("/pres4.txt", [](){
   text_p4 = (String)pres4;
   server.send(200, "text_p4/html", text_p4);
 });
  server.on("/pres5.txt", [](){
   text_p5 = (String)pres5;
   server.send(200, "text_p5/html", text_p5);
 });
  server.on("/pres6.txt", [](){
   text_p6 = (String)pres6;
   server.send(200, "text_p6/html", text_p6);
 });
 ////////send ultrasonic data////////
   server.on("/dist1.txt", [](){
   text_d1 = (String)dist1;
   server.send(200, "text_d1/html", text_d1);
 });
 server.on("/dist2.txt", [](){
   text_d2 = (String)dist2;
   server.send(200, "text_d2/html", text_d2);
 });
  server.on("/dist3.txt", [](){
   text_d3 = (String)dist3;
   server.send(200, "text_d3/html", text_d3);
 });
  server.on("/dist4.txt", [](){
   text_d4 = (String)dist4;
   server.send(200, "text_d4/html", text_d4);
 });
//  server.on("/warning.txt", [](){
//   text_warn = (String)warning;
//   server.send(200, "text_warn/html", text_warn);
// });
 
  }


void wait(int interval)
{
  unsigned long timenow = 0;
  timenow = micros();
  while(millis() < timenow + interval){}
  timenow = 0;
  }

  void data_mux(uint8_t board_num, float data)
{
  if(data <= 110 && data>= 0)
  {
    Board_data[board_num][0] = data;
  }
  else if(data >= 500 && data <= 600)
  {
    Board_data[board_num][1] = data-500;
  }
  else if(data >= 10000 && data <= 20000)
  {
    Board_data[board_num][2] = (data-10000);
  }
}
