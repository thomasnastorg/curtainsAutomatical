//Bibliothèques
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <ezTime.h>
/*#include <ESPAsyncWebServer.h>
#include <FS.h>*/



//web server , WiFi and data base
#define ssid "Route_TN"
#define password "1234567890"
ESP8266WebServer server (80);
const int FW_VERSION = 1000;
const char* urlBase = "http://192.168.1.107/arduino/";
const char* NamModule = "humidity.ino.d1_mini";

//Variables en lien avec la gestion du temps
Timezone Paris;
String currentTimeString = "";
String minuteExtraZero = "";
int currentTime[5] = {0, 0, 0, 0, 0}; //Heure = 0, Minute = 1, Jour = 2, Mois = 3, Année = 4
char monthList[13][16] = {"", "janvier", "février", "mars", "avril", "mai", "juin", "juillet", "août", "septembre", "octobre", "novembre", "décembre"}; //Le premier est vide sinon janvier serait 0 au lieu de 1
int eventOuvertureRideaux = 0;
int eventFermetureRideaux = 0;
int jourAJour = 0;

//Variables en lien avec les moteurs
const int stepPin = 4;
const int dirPin = 5;
const int enablePin = 14;
const int stepsMaxBeforeReset = 999;
const int totalRotations = 150;
int compteurOuverture = 0;
const int delayStep = 200;

//Capteurs
const int pushButton = 13;
const int colorSensor = 12;
const int lightSensor = A0;

//Variables etat rideaux et mode rideaux
bool etatRideaux = 0; //Fermés = 0, Ouverts = 1
bool etatRideauxVoulu = 1; //Fermés = 0, Ouverts = 1
bool allOk = 1;
int modeRideaux = 2; // Luminosité = 0, Minuterie = 1, Manuel = 2
String minuterieOuverture = "";
String minuterieFermeture = "";

//Variables debounce bouton poussoir
unsigned long lastPress = 0;
const int debounceDelay = 1000;

//Variables à afficher sur l'interface
const char interfaceEtatRideaux[2][50] = {"Fermés <i class='fas fa-moon'></i>", "Ouverts <i class='material-icons'>wb_sunny</i>"};
const char interfaceModeRideaux[3][70] = {"Luminosité <i class='material-icons'>brightness_auto</i>", "Minuterie <i class='fas fa-clock'></i>", "Manuel <i class='material-icons'>pan_tool</i>"};
String interfaceMinuterie = "";
String interfaceErreur = "";

//OUVERTURE DES RIDEAUX (FAIT TOURNER LE MOTEUR JUSQU'À CE QUE LE CAPTEUR DE COULEUR DÉTECTE LA LIGNE NOIRE)
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
      interfaceErreur = " - ERREUR OUVERTURE";
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


void getLuminosite()
{
  int valeurLuminosite = analogRead(lightSensor);
  if(valeurLuminosite < 180)
  {
    etatVouluFerme();
  }
  else if(valeurLuminosite > 600)
  {
    etatVouluOuvert();
  }
}

String getPage()
{
  String page = "<!DOCTYPE html>";
page += "<html lang='fr'>";
page += "<head>";
  page += "<title>Rideaux Automatisés</title>";
  page += "<meta http-equiv='refresh' content='60' name='viewport' content='width=device-width, initial-scale=1'/>";
  page += "<meta charset='UTF-8'>";
  page += "<link rel='stylesheet' href='https://www.w3schools.com/w3css/4/w3.css'>";
  page += "<link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.0/css/all.css' integrity='sha384-lZN37f5QGtY3VHgisS14W3ExzMWZxybE1SJSEsQp9S+oqd12jhcu+A56Ebc1zFSJ' crossorigin='anonymous'>";
  page += "<link href='https://fonts.googleapis.com/icon?family=Material+Icons' rel='stylesheet'>";
page += "</head>";
page += "<body>";

  page += "<!-- Titre -->";
  page += "<div class='w3-card w3-green w3-padding-16 w3-xxxlarge w3-center'>";
    page += "<p>Rideaux Automatisés</p>";
  page += "</div>";

  

  page += "<hr>";

  page += "<!-- Heure actuelle -->";
  page += "<div class='w3-center'>";
    page += "<h1>"; page += currentTime[0]; page += ":"; page += minuteExtraZero; page += currentTime[1]; page += " - "; page += currentTime[2]; page += " "; page += monthList[currentTime[3]]; page += " "; page += currentTime[4]; page += interfaceErreur; page += "</h1>";
  page += "</div>";

  page += "<hr>";

  page += "<!-- État actuel rideaux -->";
  page += "<table class='w3-table w3-bordered w3-card-4 w3-centered w3-xlarge w3-section'>";
    page += "<tr>";
      page += "<th class='w3-light-blue'>État des rideaux</th>";
      page += "<th class='w3-light-blue'>Mode</th>";
      page += "<th class='w3-light-blue'>Minuterie</th>";
    page += "</tr>";
    page += "<tr>";
      page += "<td class='w3-white' style='width:33%;'><p>"; page += interfaceEtatRideaux[etatRideaux]; page += "</p></td>";
      page += "<td class='w3-white' style='width:33%;'><p>"; page += interfaceModeRideaux[modeRideaux]; page += "</p></td>";
      page += "<td class='w3-white' style='width:33%;'><p>"; page += interfaceMinuterie; page += "</p></td>";
    page += "</tr>";
  page += "</table>";

  page += "<hr>";

  page += "<!--Contrôle manuel des rideaux -->";
  page += "<table class='w3-table-all w3-card-4 w3-center w3-section'>";
    page += "<tr>";
      page += "<th colspan='2' class='w3-light-blue'>";
        page += "<p class='w3-xlarge w3-center'>Contrôle manuel des rideaux</p>";
      page += "</th>";
    page += "</tr>";
    page += "<tr class='w3-white'>";
      page += "<td style='width:45%;'><form class='w3-center w3-border-0 w3-container' action='/toggle-etat-voulu' method='POST'><button class='w3-btn w3-white w3-ripple w3-mobile w3-xxlarge w3-padding-large w3-section' style='border-style:solid; border-width:1px; width:100%;' type='button submit' name='toggle-etat-voulu' value='1'>Ouvrir</button></form></td>";
      page += "<td style='width:45%;'><form class='w3-center w3-border-0 w3-container' action='/toggle-etat-voulu' method='POST'><button class='w3-btn w3-white w3-ripple w3-mobile w3-xxlarge w3-padding-large w3-section' style='border-style:solid; border-width:1px; width:100%;' type='button submit' name='toggle-etat-voulu' value='0'>Fermer</button></form></td>";
    page += "</tr>";
  page += "</table>";

  page += "<hr>";

  page += "<!-- Contrôle automatique des rideaux -->";
  page += "<table class='w3-table-all w3-card-4 w3-center w3-section'>";
    page += "<tr>";
      page += "<th colspan='3' class='w3-light-blue'>";
        page += "<p class='w3-xlarge w3-center'>Contrôle automatisé des rideaux</p>";
      page += "</th>";
    page += "</tr>";
    page += "<tr class='w3-white'>";
      page += "<td style='width:33%;'><form class='w3-center w3-border-0 w3-container' action='/toggle-mode' method='POST'><button class='w3-btn w3-white w3-ripple w3-mobile w3-xxlarge w3-padding-large w3-section' style='border-style:solid; border-width:1px; width:100%;' type='button submit' name='toggle-mode' value='0'>Luminosité</button></form></td>";
      page += "<td style='width:33%;'><form class='w3-center w3-border-0 w3-container' action='/toggle-mode' method='POST'><button class='w3-btn w3-white w3-ripple w3-mobile w3-xxlarge w3-padding-large w3-section' style='border-style:solid; border-width:1px; width:100%;' type='button submit' name='toggle-mode' value='1'>Minuterie</button></form></td>";
      page += "<td style='width:33%;'><form class='w3-center w3-border-0 w3-container' action='/toggle-mode' method='POST'><button class='w3-btn w3-white w3-ripple w3-mobile w3-xxlarge w3-padding-large w3-section' style='border-style:solid; border-width:1px; width:100%;' type='button submit' name='toggle-mode' value='2'>Désactiver</button></form></td>";
    page += "</tr>";
  page += "</table>";

  page += "<hr>";

  page += "<!-- Réglages de la minuterie -->";
  page += "<table class='w3-table-all w3-card-4 w3-center w3-section'>";
    page += "<tr>";
      page += "<th colspan='3' class='w3-light-blue'>";
        page += "<p class='w3-xlarge w3-center'>Réglages de la minuterie</p>";
      page += "</th>";
    page += "</tr>";
    page += "<tr class='w3-white'>";
      page += "<td>";
        page += "<br>";
        page += "<br>";
        page += "<form class='w3-border-0 w3-container w3-xxlarge' action='/timer-settings' method='POST'>";
          page += "<select class='w3-select' name='timer-open'>";
            page += "<option value=''>Heure d'ouverture des rideaux</option>";
            page += "<option value='04:00'>4:00</option>";
            page += "<option value='04:30'>4:30</option>";
            page += "<option value='05:00'>5:00</option>";
            page += "<option value='05:30'>5:30</option>";
            page += "<option value='06:00'>6:00</option>";
            page += "<option value='06:30'>6:30</option>";
            page += "<option value='07:00'>7:00</option>";
            page += "<option value='07:30'>7:30</option>";
            page += "<option value='08:00'>8:00</option>";
            page += "<option value='08:30'>8:30</option>";
            page += "<option value='09:00'>9:00</option>";
            page += "<option value='09:30'>9:30</option>";
            page += "<option value='10:00'>10:00</option>";
            page += "<option value='10:30'>10:30</option>";
            page += "<option value='11:00'>11:00</option>";
          page += "</select>";
          page += "<br>";
          page += "<br>";
          page += "<select class='w3-select w3-center' name='timer-close'>";
            page += "<option value=''>Heure de fermeture des rideaux</option>";
            page += "<option value='16:00'>16:00</option>";
            page += "<option value='16:30'>16:30</option>";
            page += "<option value='17:00'>17:00</option>";
            page += "<option value='17:30'>17:30</option>";
            page += "<option value='18:00'>18:00</option>";
            page += "<option value='18:30'>18:30</option>";
            page += "<option value='19:00'>19:00</option>";
            page += "<option value='19:30'>19:30</option>";
            page += "<option value='20:00'>20:00</option>";
            page += "<option value='20:30'>20:30</option>";
            page += "<option value='21:00'>21:00</option>";
            page += "<option value='21:30'>21:30</option>";
            page += "<option value='22:00'>22:00</option>";
            page += "<option value='22:30'>22:30</option>";
            page += "<option value='23:00'>23:00</option>";
          page += "</select>";
          page += "<br>";
          page += "<br>";
          page += "<button class='w3-btn w3-white w3-ripple w3-mobile w3-xxxlarge w3-padding-large w3-section' style='border-style:solid; border-width:1px; width:100%;' type='button submit' name='timer-apply'>Appliquer</button>";
        page += "</form>";
      page += "</td>";
    page += "</tr>";
  page += "</table>";

page += "</body>";
page += "</html>";
return page;
}

void handleRoot()
{
  server.send(200, "text/html", getPage());
}

void handleToggleEtatVoulu()
{
  etatRideauxVoulu = server.arg("toggle-etat-voulu").toInt();
  modeRideaux = 2;
  server.sendHeader("Location","/");
  server.send(303);
}

void updateMinuterie()
{
  if(eventOuvertureRideaux)
  {
    deleteEvent(eventOuvertureRideaux);
    eventOuvertureRideaux = 0;
  }

  if(eventFermetureRideaux)
  {
    deleteEvent(eventFermetureRideaux);
    eventFermetureRideaux = 0;
  }

  if(modeRideaux == 1)
  {
    if(minuterieOuverture <= "")
      minuterieOuverture = "08:00";

    if(minuterieFermeture <= "")
      minuterieFermeture = "21:00";

    String tempMinuteString;
    int tempMinute;
    String tempHeureString;
    int tempHeure;

    tempHeureString = String(minuterieOuverture[0]) + String(minuterieOuverture[1]);
    tempMinuteString = String(minuterieOuverture[3]) + String(minuterieOuverture[4]);
    tempHeure = tempHeureString.toInt();
    tempMinute = tempMinuteString.toInt();

    if(currentTime[0] <= tempHeure)
        eventOuvertureRideaux = Paris.setEvent(*etatVouluOuvert, tempHeure, tempMinute, 0, currentTime[2], currentTime[3], currentTime[4]);

    tempHeureString = String(minuterieFermeture[0]) + String(minuterieFermeture[1]);
    tempMinuteString = String(minuterieFermeture[3]) + String(minuterieFermeture[4]);
    tempHeure = tempHeureString.toInt();
    tempMinute = tempMinuteString.toInt();

    if(currentTime[0] <= tempHeure)
        eventFermetureRideaux = Paris.setEvent(*etatVouluFerme, tempHeure, tempMinute, 0, currentTime[2], currentTime[3], currentTime[4]);

    if(minuterieOuverture)
      interfaceMinuterie = "Ouverture " + minuterieOuverture + ", ";
    else
      interfaceMinuterie = "Ouverture <i class='fas fa-times-circle w3-xxlarge'></i>, ";

    if(minuterieFermeture)
      interfaceMinuterie += "fermeture " + minuterieFermeture + ".";
    else
      interfaceMinuterie += "fermeture <i class='fas fa-times-circle w3-xxlarge'></i>.";
  }
  else
    interfaceMinuterie = "<i class='fas fa-times-circle w3-xxlarge'></i>";
}

void handleToggleMode()
{
  modeRideaux = server.arg("toggle-mode").toInt();
  if(modeRideaux != 1)
    updateMinuterie();
  server.sendHeader("Location","/");
  server.send(303);
}

void handleTimerSettings()
{
  minuterieOuverture = server.arg("timer-open");
  minuterieFermeture = server.arg("timer-close");

  updateMinuterie();
  server.sendHeader("Location","/");
  server.send(303);
}

void handleNotFound()
{
  server.send(404, "text/plain", "404: Not found");
}

void getCurrentTime()
{
  currentTimeString = Paris.dateTime();
  currentTime[0] = Paris.hour();

  int temp = Paris.minute();

  if(temp < 10)
    minuteExtraZero = "0";
  else
    minuteExtraZero = "";

  currentTime[1] = temp;

  currentTime[2] = Paris.day();
  currentTime[3] = Paris.month();
  currentTime[4] = Paris.year();
}

void checkPushButton()
{
  if (digitalRead(pushButton))
  {
    if((millis() - lastPress) >= debounceDelay)
    {
      lastPress = millis();
      etatRideauxVoulu = !etatRideauxVoulu;
      modeRideaux = 2;
      updateMinuterie();
    }
  }
}



int dayChanged()
{
  if(jourAJour != currentTime[2])
    {
      jourAJour = currentTime[2];
      updateMinuterie();
      return 1;
    }
    else
      return 0;
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


//Setup ----------------------------------------------------------------------------------------------------------------------------------------------- Setup
void setup()
{
  Serial.begin(115200);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);

  pinMode(pushButton, INPUT);
  pinMode(colorSensor, INPUT);
  pinMode(lightSensor, INPUT);

  digitalWrite(enablePin, HIGH);

  initialiserRideaux();

  WiFi.softAPdisconnect(true);
  WiFi.persistent(false);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay (500);
  }

  setDebug(DEBUG);
  waitForSync();
  Paris.setLocation("Europe/Paris");
  Paris.setDefault();
  getCurrentTime();
  jourAJour = currentTime[2];
  updateMinuterie();

  server.on("/", HTTP_GET, handleRoot);
  server.on("/toggle-etat-voulu", HTTP_POST, handleToggleEtatVoulu);
  server.on("/toggle-mode", HTTP_POST, handleToggleMode);
  server.on("/timer-settings", HTTP_POST, handleTimerSettings);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.println("Setup done");
  Serial.println(WiFi.localIP());
}

//Loop ------------------------------------------------------------------------------------------------------------------------------------------------ Loop
void loop()
{
  server.handleClient();
  events();

  //VÉRIFICATION ÉTATS
  checkEtats();

  //BOUTON POUSSOIR
  checkPushButton();
  
  //Mise à jour de l'heure et lecture de la luminosité
  if(minuteChanged())
  {
    getCurrentTime();
    if(!modeRideaux)
      getLuminosite();
  }

  //Mise à jour de la minuterie quand on change de jour
  if(dayChanged())
    updateMinuterie();
}
