//  Bibliothéque 
#include <Arduino.h> //couc
#include <ESP8266WiFi.h> //tes avec la mac
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ezTime.h>
#include <MQTTClient.h>
#include <MQTT.h>
#include <SPI.h>
#include "config.h"
#include "update.h"
//


void windo(){

}

void ouvrirRideaux()
{
  //COUNTERCLOCKWISE
  digitalWrite(dirPin, HIGH);
  digitalWrite(enablePin, LOW);

  while(!digitalRead(colorSensor))
  {
    for (int j = 0; j < stepsMaxBeforeReset; j++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(delayStep);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(delayStep);
      Serial.println("colore: " + String(digitalRead(colorSensor)));
    }
    compteurOuverture++;
    if(compteurOuverture >= 151)
    {
      allOk = 0;
      
      break;
    }
    yield();
  }

  compteurOuverture = 0;
  digitalWrite(enablePin, HIGH);
  etatRideaux = etatRideauxVoulu;
}

//FERMETURE DES RIDEAUX (FAIT TOURNER LE MOTEUR UN NOMBRE DE ROTATIONS DÉFINIT)
void fermerRideaux(int nbRotations)
{
  //CLOCKWISE
  digitalWrite(dirPin, LOW);
  digitalWrite(enablePin, LOW);

  for(int i = 0; i < nbRotations; i++)
  {
    for (int j = 0; j < stepsMaxBeforeReset; j++)
    {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(delayStep);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(delayStep);
    }
    yield();
  }

  digitalWrite(enablePin, HIGH);
  etatRideaux = etatRideauxVoulu;
}

void etatVouluOuvert()
{
  etatRideauxVoulu = 1;
}

void etatVouluFerme()
{
  etatRideauxVoulu = 0;
}

void initialiserRideaux()
{
  etatRideaux = digitalRead(colorSensor);

  if(!etatRideaux) //si fermer
    ouvrirRideaux();// ouvrire
  else // si ouver
  {
    fermerRideaux(10);
    ouvrirRideaux();
  }
}

//MQTT to connect 
void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnecting to broker...");
  while (!client.connect("arduino", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }
}

//MQTT recieved message 

void subscribemessage(){
  Serial.println("connecting to channel broker");
  client.subscribe("curtains/statenow");
  client.subscribe("curtains/statewant");
  client.subscribe("curtains/mode");
  client.subscribe("curtains/pourcent");

} 

void messageReceived(String &topic, String &payload) {
  
 if(topic == "curtains/statewant")
 {
 etatRideauxVoulu = payload.toInt();
 }
 //else if (topic == "curtains/pourcent")
 // = payload.toInt();
 else if (topic == "curtains/mode")
 {
modeRideaux = payload.toInt();
}

 else
 {
   Serial.println("is the wong message");
 }
  //modeRideaux("curtains/mode",payload);
  
}

void checkEtats()
{
  if(allOk)
  {
    if(etatRideauxVoulu != etatRideaux)
    {
      if(etatRideauxVoulu)
        ouvrirRideaux();
      else
        fermerRideaux(totalRotations);
    }
  }
}


void setup(){
  Serial.begin(115200);

  /*Serial.print(" is Connecting to "); /: we used for update arduino
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    
    ESP.restart();
    
  }*/

  

    
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
    

  pinMode(pushButton, INPUT);
  pinMode(colorSensor, INPUT);
  pinMode(statewindo, INPUT);
  digitalWrite(enablePin, HIGH);

  initialiserRideaux();

  Serial.println(" is Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  client.begin(brokerip, net);
  
  
  connect();
  subscribemessage();
}



void loop()
{

  client.loop();

  if (!client.connected()) {
    connect();
    subscribemessage();
  }

client.onMessage(messageReceived);
Serial.println("-----------");
Serial.println(modeRideaux);
Serial.println(etatRideauxVoulu);
Serial.println(etatRideaux);
delay(3000);
  
}


