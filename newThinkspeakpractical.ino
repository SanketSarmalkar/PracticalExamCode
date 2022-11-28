
//https://www.electroniclinic.com/
// Download Libraries: https://www.electroniclinic.com/arduino-libraries-download-and-projects-they-are-used-in-project-codes/

#include "ThingSpeak.h"
//#include "secrets.h" // secrets.h code is already given above in the first example
#include <ESP8266WiFi.h>

const int trigPin = 5;
const int echoPin = 4;

long duration;
float distance;

#define SECRET_SSID "SanketSarmalkar"        // replace MySSID with your WiFi network name
#define SECRET_PASS "Sanket123456789"   // replace MyPassword with your WiFi password

#define SECRET_CH_ID 1958518           // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "P1I2HWN1HVZM9DA8"   // replace XYZ with your channel write API Key

char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

// Initialize our values

int number1 = 0;
int number2 = random(0,100);
int number3 = random(0,100);
int number4 = random(0,100);
String myStatus = "";

// sensor
int Pot = A0; 
void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(12, INPUT);
  Serial.begin(115200);  // Initialize serial
  //pinMode(Pot,INPUT); 
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.39)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(1000);
//int data = map(analogRead(Pot),0,1023,0,255);
  // set the fields with the values
  ThingSpeak.setField(1, distance);
//  ThingSpeak.setField(2, number2);
//  ThingSpeak.setField(3, number3);
//  ThingSpeak.setField(4, number4);
/*
  // figure out the status message
  if(number1 > number2){
    myStatus = String("field1 is greater than field2"); 
  }
  else if(number1 < number2){
    myStatus = String("field1 is less than field2");
  }
  else{
    myStatus = String("field1 equals field2");
  }
  
  // set the status
  ThingSpeak.setStatus(myStatus);
*/  
  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  if(digitalRead(12) == HIGH){
    digitalWrite(16,HIGH);
    delay(1000);
    digitalWrite(16,LOW);
  }
  /*
  // change the values
  number1++;
  if(number1 > 99){
    number1 = 0;
  }
  number2 = random(0,100);
  number3 = random(0,100);
  number4 = random(0,100);
  */
  delay(1000); // Wait 20 seconds to update the channel again
}
