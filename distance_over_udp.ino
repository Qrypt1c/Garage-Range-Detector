/*
  WiFi UDP Send

 This sketch sends UDP packet containing distance data

 */


#include <SPI.h>
#include <WiFiNINA.h>
#include <WiFiUdp.h>

int status = WL_IDLE_STATUS;
#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key index number (needed only for WEP)

unsigned int localPort = 2390;      // local port to listen on
char  ReplyBuffer[16];

char packetBuffer[256]; //buffer to hold incoming packet

int red = 12;
int green = 11;
int blue = 10;

int trigger = 14;
int echo = 15;

float duration = 0;
float distance = 0;

WiFiUDP Udp;

void setup() {
  //Initialize serial and wait for port to open:
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
  //while (!Serial) {
  //  ; // wait for serial port to connect. Needed for native USB port only
  //}
  

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to WiFi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(5000);
  }
  Serial.println("Connected to WiFi");
  printWifiStatus();
  Udp.begin(localPort);
}

void loop() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  duration = pulseIn(echo, HIGH);

  int distance_cm = ((duration * 0.034) / 2);

  if (distance_cm < 103 && distance_cm > 90){
    colorfn(green);
  }

  else{
    colorfn(red);
  }

  Serial.print("Distance = ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  //ltoa(distance_cm, ReplyBuffer, 15);
  //Serial.println(ReplyBuffer);
    
  Serial.println("Sending packet now...");
  // send a reply, to the IP address and port that sent us the packet we received
  Udp.beginPacket(IPAddress(192,168,1,77), 7203);
  Udp.print(distance_cm);
  Udp.endPacket();
}

void colorfn(int color){
  digitalWrite(color, HIGH);
  delay(2000);
  digitalWrite(color, LOW);
  delay(1000);
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
