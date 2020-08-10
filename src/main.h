//  Bibliothéque 
#include <Arduino.h> //couc
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ezTime.h>

//

#define ssid "Route_TN"
#define password "1234567"
const int FW_VERSION = 1000;
const char* urlBase = "http://192.168.1.107/arduino/"; // ****  update url  **** 
const char* NamModule = "humidity.ino.d1_mini";

//Variables en lien avec les moteurs
const int stepPin = 4;
const int dirPin = 5;
const int enablePin = 14;
const int stepsMaxBeforeReset = 999;
const int totalRotations = 150;
int compteurOuverture = 0;
const int delayStep = 200;

//Capteursff
const int pushButton = 13;
const int colorSensor = 12;
const int statewindo = A0;

bool etatRideaux = 0; //Fermés = 0, Ouverts = 1
bool etatRideauxVoulu = 1; //Fermés = 0, Ouverts = 1
bool allOk = 1;
int modeRideaux = 2; // Luminosité = 0, Minuterie = 1, Manuel = 2

//Variables debounce bouton poussoir
unsigned long lastPress = 0;
const int debounceDelay = 1000;

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

// automatic update
void checkForUpdates() {
  String Nam = String( NamModule );;
  String fwURL = String( urlBase );
  fwURL.concat( Nam );
  String fwVersionURL = fwURL;
  fwVersionURL.concat( ".version" );

  Serial.println( "Checking for firmware updates." );
  Serial.print( "Nam" );
  Serial.println( Nam );
  Serial.print( "Firmware version URL: " );
  Serial.println( fwVersionURL );

  HTTPClient httpClient;
  httpClient.begin( fwVersionURL );
  int httpCode = httpClient.GET();
  if( httpCode == 200 ) {
    String newFWVersion = httpClient.getString();

    Serial.print( "Current firmware version: " );
    Serial.println( FW_VERSION );
    Serial.print( "Available firmware version: " );
    Serial.println( newFWVersion );

    int newVersion = newFWVersion.toInt();

    if( newVersion > FW_VERSION ) {
      Serial.println( "Preparing to update" );

      String fwImageURL = fwURL;
      fwImageURL.concat( ".bin" );
      t_httpUpdate_return ret = ESPhttpUpdate.update( fwImageURL );

      switch(ret) {
        case HTTP_UPDATE_FAILED:
          Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
          break;

        case HTTP_UPDATE_NO_UPDATES:
          Serial.println("HTTP_UPDATE_NO_UPDATES");
          break;
      }
    }
    else {
      Serial.println( "Already on latest version" );
    }
  }
  else {
    Serial.print( "Firmware version check failed, got HTTP response code " );
    Serial.println( httpCode );
  }
  httpClient.end();
}


void setup(){
  Serial.begin(115200);
  Serial.print(" is Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    
    ESP.restart();
    
  }

  checkForUpdates(); 

    
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    

    pinMode(pushButton, INPUT);
    pinMode(colorSensor, INPUT);
    pinMode(statewindo, INPUT);
    digitalWrite(enablePin, HIGH);
  initialiserRideaux();
    
}

void loop()
{

}
