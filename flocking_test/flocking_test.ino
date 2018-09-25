/* 
 * Mert Arduino and Tech - YouTube
 * WiFi Robot controlled by Phone (WiFibot/Android/IoT/ESP8266)
 * NodeMCU ESP8266 Tutorial 03
 * Please Subscribe for Support - https://goo.gl/RLT6DT
 */


/* include library */
#include <ESP8266WiFi.h>

/*
 * If you have no idea about this library, you can watch the tutorial below
 * NodeMCU ESP8266 Tutorial 01: Programming NodeMCU ESP-12E Using Arduino IDE
 * https://youtu.be/NtyFx1frYB0
 */

 /* WIFI settings */
const char* ssid = "RobertHitler";
const char* password = "HackingPrince71";

/* define port */
WiFiClient client;
WiFiServer server(80);

/* data received from application */
String  data =""; 

/* define L298N or L293D motor control pins */
int IN1 = D5;     /* GPIO2(D4) -> IN3   */
int IN2 = D6;   /* GPIO15(D8) -> IN1  */
int IN3 = D7;    /* GPIO0(D3) -> IN4   */
int IN4 = D8;  /* GPIO13(D7) -> IN2  */


/* define L298N or L293D enable pins */
int ENB_1 = D3; /* GPIO14(D5) -> Motor-A Enable */
int ENB_2 = D4;  /* GPIO12(D6) -> Motor-B Enable */

void setup(){
  Serial.begin(115200);
  delay(10);
  connectWiFi();
  /* initialize motor control pins as output */
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);  
  pinMode(IN4, OUTPUT);

  /* initialize motor enable pins as output */
  pinMode(ENB_1, OUTPUT); 
  pinMode(ENB_2, OUTPUT);

  /* start server communication */
  server.begin();
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();

/************************ Run function according to incoming data from application *************************/

    /* If the incoming data is "forward", run the "MotorForward" function */
    if (data == "forward") MotorForward();
    /* If the incoming data is "backward", run the "MotorBackward" function */
    else if (data == "reverse") MotorBackward();
    /* If the incoming data is "left", run the "TurnLeft" function */
    else if (data == "left") TurnLeft();
    /* If the incoming data is "right", run the "TurnRight" function */
    else if (data == "right") TurnRight();
    /* If the incoming data is "stop", run the "MotorStop" function */
    else if (data == "stop") MotorStop();
} 

/********************************************* FORWARD *****************************************************/
void MotorForward(void)   
{
  digitalWrite(ENB_1,HIGH);
  digitalWrite(ENB_2,HIGH);
  //analogWrite(ENB_1,200);
  //analogWrite(ENB_2,200);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN4,LOW);
  
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)   
{
  digitalWrite(ENB_1,HIGH);
  digitalWrite(ENB_2,HIGH);
  //analogWrite(ENB_1,200);
  //analogWrite(ENB_2,200);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN4,HIGH);
  digitalWrite(IN1,LOW);
  digitalWrite(IN3,LOW);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{
  digitalWrite(ENB_1,LOW);
  digitalWrite(ENB_2,HIGH);
  //analogWrite(ENB_1,10);
  //analogWrite(ENB_2,200); 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);  
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)   
{
  digitalWrite(ENB_1,HIGH);
  digitalWrite(ENB_2,LOW);
  //analogWrite(ENB_1,200);
  //analogWrite(ENB_2,10);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

/********************************************* STOP *****************************************************/
void MotorStop(void)   
{
  digitalWrite(ENB_1,LOW);
  digitalWrite(ENB_2,LOW);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}

/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
