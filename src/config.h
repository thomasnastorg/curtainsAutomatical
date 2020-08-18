// WIFI
#define ssid "Route_TN"
#define password "1234567890"
//const int FW_VERSION = 1000;
//const char* urlBase = "http://192.168.1.107/arduino/"; // ****  update url  **** 
//const char* NamModule = "humidity.ino.d1_mini";

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
int modeRideaux = 2; // 0 = deffaut 1 = normally 2 = time 3 = manuel by poucent 


// MQTT
// Source https://github.com/256dpi/arduino-mqtt
WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

char brokerip[] = "192.168.1.105";

//Variables debounce bouton poussoir
unsigned long lastPress = 0;
const int debounceDelay = 1000;
