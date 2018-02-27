#include <MicroGear.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "DHT.h"

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

//String Messages =  "0.23,0.23,2.90,252.11,224.61,211.92" ;
int volt[10];
int amp[10];
float value[10];
const int numberOfPieces = 10;
int pieces[numberOfPieces];
int lastIndex = 0;
int counter = 0;
int S_Toggle1 = 0;
int S_Toggle2 = 0;
int S_Toggle3 = 0;
int S_Toggle4 = 0;
int S_Blower = 0;

//const char* ssid     = "Horizon_Plus";
//const char* password = "1212312121";
//const char* ssid     = "Horizon_PC";
//const char* password = "1212312121";
const char* ssid     = "EESS_IOT_WIFI";
const char* password = "1212312121";
#define LEDPin 15 
#define APPID   "SmartFactoryPilot"
#define KEY     "t6AgTfL1PHIhf0h"
#define SECRET  "Daq2JADYHcU0dZYEd01YWDHg1"
#define FREEBORADALIAS       "free_ledtest"

// Timer interval
unsigned long previousMillis = 0;       //กำหนดตัวแปรเก็บค่า เวลาสุดท้ายที่ทำงาน    
const long interval = 1000;            //กำหนดค่าตัวแปร ให้ทำงานทุกๆ 10 วินาที
int Count_Check =0;

#define ALIAS   "NodeMCU1"
#define TargetWeb "HTML_web"

#define D0 16  // USER LED Wake
#define D1 5
#define D2 4   // TOGGLE 1
#define D3 0   // FLASH
#define D4 2   // TXD1 , DHT22 ****
#define D5 14  // TOGGLE 2
#define D6 12  // TOGGLE 3
#define D7 13  // RXD2
#define D8 15  // TXD2,LED4 **** TOGGLE 4
#define D9 3   // RXD0
#define D10 1  // TXD0,LED5 / Blower 
#define SD2 9
#define SD3 10

#define DHTPIN D4     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

String Ck_chanel[10] ;

WiFiClient client;
MicroGear microgear(client);

//Time starmp set

unsigned int localPort = 2390;      // local port to listen for UDP packets
unsigned long timestamp ;
/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;



void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen)
{
  //=======รับ chat มาจาก NETPIE freeboard===========
  Serial.print("Incoming message --> ");
  Serial.print(topic);
  Serial.print(" : ");
  char strState[msglen];
  for (int i = 0; i < msglen; i++)
  {
    strState[i] = (char)msg[i];
    Serial.print((char)msg[i]);
  }
  Serial.println();
  String stateStr = String(strState).substring(0, msglen);
  
  On_Msg_Check(topic,stateStr);
 
}


void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
    Serial.println("Connected to NETPIE...");
    microgear.setAlias(ALIAS);
}

void setup() 
{
     /* Event listener */
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(CONNECTED,onConnected);
    
    pinMode(D2, OUTPUT);
    pinMode(D5, OUTPUT);
    pinMode(D6, OUTPUT);
    pinMode(D8, OUTPUT);
    pinMode(D10, OUTPUT);
    
    dht.begin();
    Serial.begin(115200);
    Serial.println("Starting...");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
       delay(250);
       Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
    microgear.subscribe("/Blower");
    microgear.subscribe("/Factory/#");


    ArduinoOTA.onStart([]()
  {
   Serial.println("Start");
  });
  ArduinoOTA.onEnd([]()
  {
    Serial.println("End");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
  {
    Serial.printf("Progress: %u%%\n", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error)
  {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
    ESP.restart();
  });

  ArduinoOTA.begin(); // setup the OTA server
}

void loop() 
{
    serialEvent();
    NetpieService();
    ArduinoOTA.handle();
    delay(1500);
}





String Get_Temp(){
       float Humidity = dht.readHumidity();
       float Temp = dht.readTemperature();  // Read temperature as Celsius (the default)
       String data =   String(Humidity) + "/" + String(Temp);
       char msg[128];
       data.toCharArray(msg,data.length());
       //Serial.println(msg);    
       //microgear.chat(ALIAS , msg);
       return data;
}

unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}


